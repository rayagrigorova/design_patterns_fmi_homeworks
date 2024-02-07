#include "FollowBuilder.h"

#include <windows.h>
#include <shobjidl.h>
#include <string>
#include <ShlObj.h>
#include <iostream>
#include <windows.h>

namespace {
    // !!!!
    // The section of code below was developed with the assistance of OpenAI's ChatGPT.

    std::string findShortcutPath(const std::wstring& shortcutPath) {
        IShellLinkW* psl;
        WCHAR resolvedPath[MAX_PATH];
        HRESULT hres = CoInitialize(NULL); // This initializes a COM library for the current thread

        if (FAILED(hres)) {
            return "";
        }

        // Create an instance of the ShellLink object
        hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (void**)&psl);
        if (SUCCEEDED(hres)) {
            IPersistFile* ppf; // Used to load the shortcut file 

            // Get the IPersistFile interface from the IShellLink interface
            hres = psl->QueryInterface(IID_IPersistFile, (void**)&ppf);
            if (SUCCEEDED(hres)) {
                // Load the shortcut file
                hres = ppf->Load(shortcutPath.c_str(), STGM_READ);
                if (SUCCEEDED(hres)) {
                    // Resolve the link to get the target path
                    hres = psl->GetPath(resolvedPath, MAX_PATH, NULL, SLGP_UNCPRIORITY);
                    ppf->Release(); 
                }
            }
            psl->Release();
        }

        CoUninitialize(); // Uninitialize COM library

        return std::string(resolvedPath, resolvedPath + wcslen(resolvedPath));
    }
}


std::unique_ptr<AbstractFile> FollowBuilder::buildLink(const fs::path& path) {
    // Here I am checking if the path to the link (not the directory) was already added 
    // This way the same link will not be handled twice. 
    if (visited.count(path)) { 
        return nullptr;
    }
    visited.insert(path);

    if (fs::is_symlink(path)) {
        try {
            fs::path link = fs::read_symlink(path);
            if (fs::is_regular_file(link)) {
                return buildFile(link);
            }
            return buildDir(link);
        }
        catch (const fs::filesystem_error& e) {
            std::cerr << "Error when reading symbolic link" << e.what() << std::endl;
            return nullptr;
        }
    }
    // Handling a windows shortcut is not as straightforward
    fs::path link = findShortcutPath(path); 

    if (fs::is_regular_file(link)) {
        return buildFile(link);
    }
    return buildDir(link);
}
