#include "NoFollowBuilder.h"

std::unique_ptr<AbstractFile> NoFollowBuilder::buildLink(const fs::path& path) {
    // The buildFile() function performs the checks whether the file was already visited 
    return buildFile(path);
}
