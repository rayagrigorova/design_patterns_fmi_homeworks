#include <filesystem>

#include "test_utils.h"

namespace fs = std::filesystem;

std::string getTestResourcePath(const std::string& resourceName) {
    fs::path testResourcesPath = fs::current_path().parent_path().parent_path() / "test" / "resources";
    return (testResourcesPath / resourceName).string();
}
