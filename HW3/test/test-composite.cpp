#include "catch2/catch_all.hpp"
#include "File.h"
#include "Directory.h"
#include <filesystem>
#include <iostream>

namespace fs = std::filesystem;
#include "test_utils.h"

TEST_CASE("Test File Sizes in compDir", "[File]") {
    fs::path pathToFile1 = fs::path(getTestResourcePath("compDir/file1.docx"));
    fs::path pathToFile2 = fs::path(getTestResourcePath("compDir/file2.docx"));

    File file1(pathToFile1);
    File file2(pathToFile2);

    SECTION("Individual File Sizes") {
        REQUIRE(file1.getSize() == 21430); 
        REQUIRE(file2.getSize() == 14191);
    }
}

TEST_CASE("Test Directory Opening in compDir", "[Directory]") {
    fs::path pathToCompDir = fs::path(getTestResourcePath("compDir"));
    Directory compDir(pathToCompDir);

    SECTION("Total Directory Size") {
        fs::path pathToFile1 = fs::path(getTestResourcePath("compDir/file1.docx"));
        fs::path pathToFile2 = fs::path(getTestResourcePath("compDir/file2.docx"));

        std::cout << pathToFile1.string() << " " << pathToFile2.string() << "\n"  << "PLEASE PRINT THIS HELOOOOO ";
        std::unique_ptr<File> f1 = std::make_unique<File>(pathToFile1);
        std::unique_ptr<File> f2 = std::make_unique<File>(pathToFile2);
        compDir.add(std::move(f1));
        compDir.add(std::move(f2));
        std::uintmax_t totalSize = compDir.getSize();
        REQUIRE(totalSize == (21430 + 14191)); 
    }
}
