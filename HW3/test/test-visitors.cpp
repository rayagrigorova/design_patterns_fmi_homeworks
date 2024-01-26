#include "catch2/catch_all.hpp"
#include <filesystem>
#include <iostream>
#include "HashStreamWriter.h"
#include "ReportWriter.h"
#include "FollowBuilder.h"
#include "NoFollowBuilder.h"
#include <memory>

namespace fs = std::filesystem;
#include "test_utils.h"

TEST_CASE("Visitor - No symbolic links test hash", "[Visitor]") {
    NoFollowBuilder builder;

    auto alg = std::make_unique<CryptoPP::SHA256>(); 
    auto res = builder.buildDir(fs::path(getTestResourcePath("dir1")));
    HashStreamWriter writer(std::cout, std::move(alg));
    writer.visitDirectory(*res);

    // REQUIRE(false);
}


TEST_CASE("Visitor - No symbolic links test hash 2", "[Visitor]") {
    NoFollowBuilder builder;

    auto alg = std::make_unique<CryptoPP::SHA256>(); 
    auto res = builder.buildDir(fs::path(getTestResourcePath("dir2")));
    ReportWriter writer(std::cout); 
    writer.visitDirectory(*res);

    // REQUIRE(false);
}

// !!! 
// The testing code for visiting a shortcut works as expected
// when run outside of the catch2 framework for some reason.
// But when the code is run using catch2, the tests fail.  
TEST_CASE("Visitor - Follow link visitor test", "[Visitor]") {
    FollowBuilder builder;

    auto res = builder.buildDir(fs::path(getTestResourcePath("dir3"))); 
    ReportWriter writer(std::cout); 
    writer.visitDirectory(*res);

    // REQUIRE(false);
}

TEST_CASE("Visitor - No follow link visitor test", "[Visitor]") {
    NoFollowBuilder builder;

    auto res = builder.buildDir(fs::path(getTestResourcePath("dir3"))); 
    ReportWriter writer(std::cout); 
    writer.visitDirectory(*res);

    // REQUIRE(false);
}

TEST_CASE("Visitor - Follow link visitor cycle test", "[Visitor]") {
    FollowBuilder builder;

    auto res = builder.buildDir(fs::path(getTestResourcePath("dir5"))); 
    ReportWriter writer(std::cout); 
    writer.visitDirectory(*res);

    // REQUIRE(false);
}
