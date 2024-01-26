#include "catch2/catch_all.hpp"
#include <filesystem>
#include <iostream>
#include "FollowBuilder.h"
#include "NoFollowBuilder.h"
#include <filesystem>
#include <memory>

namespace fs = std::filesystem;
#include "test_utils.h"

TEST_CASE("No symbolic links test", "[Builder]") {
    NoFollowBuilder builder;

    auto res = builder.buildDir(fs::path(getTestResourcePath("dir1")));
    REQUIRE(res->getSize() == 50473);
}


TEST_CASE("No symbolic links test 2", "[Builder]") {
    FollowBuilder builder;

    auto res = builder.buildDir(fs::path(getTestResourcePath("dir2")));
    REQUIRE(res->getSize() == 543449);
}

// TEST_CASE("Symbolic link test follow", "[Builder]") {
//     FollowBuilder builder;
// 
//     auto res = builder.buildDir(fs::path(getTestResourcePath("dir3")));
//     REQUIRE(res->getSize() == 544821- 2 + 42);
// }

TEST_CASE("Symbolic link test no follow", "[Builder]") {
    NoFollowBuilder builder;

    auto res = builder.buildDir(fs::path(getTestResourcePath("dir3")));
    REQUIRE(res->getSize() == 544821);
}
