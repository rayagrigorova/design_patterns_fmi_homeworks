#include "NoFollowBuilder.h"

std::unique_ptr<AbstractFile> NoFollowBuilder::buildLink(const fs::path& path) {
    return std::unique_ptr<File>(path);
}
