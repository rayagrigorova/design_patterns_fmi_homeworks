#include "NoFollowBuilder.h"

std::unique_ptr<AbstractFile> NoFollowBuilder::buildLink(const fs::path& path) const {
    return std::unique_ptr<File>(path);
}
