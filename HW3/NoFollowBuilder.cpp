#include "NoFollowBuilder.h"

std::unique_ptr<AbstractFile> NoFollowBuilder::buildLink(const fs::path& path) {
    visited.insert(path);
    return std::make_unique<File>(path);
}
