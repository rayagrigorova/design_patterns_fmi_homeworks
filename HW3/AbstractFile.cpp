#include "AbstractFile.h"

AbstractFile::AbstractFile(const fs::path& path) : path(path) {

}

const fs::path& AbstractFile::getPath() const {
    return path;
}
