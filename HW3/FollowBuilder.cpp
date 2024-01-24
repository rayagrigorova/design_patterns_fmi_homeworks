#include "FollowBuilder.h"

#include <windows.h>
#include <shobjidl.h>
#include <string>
#include <ShlObj.h>

namespace {
    // The section of code below was developed with the assistance of OpenAI's ChatGPT.
    std::string findShortcutPath(const std::wstring& shortcutPath) {
        IShellLink* psl; // IShellLink is used to work with shortcuts 
        WCHAR resolvedPath[MAX_PATH]; // array to store the resolved path
        HRESULT hres = CoInitialize(NULL); // this initializes a COM library for the current thread

        if (FAILED(hres)) {
            return "";
        }

        // Create an instance of the ShellLink object
        hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (void**)&psl);
        if (SUCCEEDED(hres)) {
            IPersistFile* ppf; // used to load the shortcut file 

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

        CoUninitialize(); // uninitialize COM library

        return std::string(resolvedPath, resolvedPath + wcslen(resolvedPath));
    }
}


std::unique_ptr<AbstractFile> FollowBuilder::buildLink(const fs::path& path) {
    if (fs::is_symlink(path)) {
        return buildDir(fs::read_symlink(path));
    }
    // Handling a windows shortcut is not as straightforward
    return buildDir(findShortcutPath(path));
}
