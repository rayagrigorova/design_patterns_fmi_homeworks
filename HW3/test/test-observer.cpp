#include "catch2/catch_all.hpp"

#include <iostream>
#include "FollowBuilder.h"
#include "NoFollowBuilder.h"
#include "ReportWriter.h"
#include "HashStreamWriter.h"
#include "ProgressReporter.h"

namespace fs = std::filesystem;
#include "test_utils.h"


// Files to be reported: word.docx, file.txt, house.png,
// powerpoint.pptx, file3.txt, file.txt, file2.txt
TEST_CASE("Observer - visit dir1", "[Observer]") {
    NullBuffer null_buffer;
    std::ostream null_stream(&null_buffer);

    NoFollowBuilder builder;

    auto alg = std::make_unique<CryptoPP::SHA256>();
    auto res = builder.buildDir(fs::path(getTestResourcePath("dir1")));
    HashStreamWriter writer(null_stream, std::move(alg));
    writer.subscribe(std::make_unique<ProgressReporter>(res->getSize()));
    writer.visitDirectory(*res);

    REQUIRE(false);
}


// Files to be reported: word.docx, file.txt, house.png, powerpoint.pptx, sadfadsa.docx 
TEST_CASE("Observer - visit dir2", "[Observer]") {
    NullBuffer null_buffer;
    std::ostream null_stream(&null_buffer);

    NoFollowBuilder builder;

    auto alg = std::make_unique<CryptoPP::SHA256>();
    auto res = builder.buildDir(fs::path(getTestResourcePath("dir2")));
    HashStreamWriter writer(null_stream, std::move(alg));
    writer.subscribe(std::make_unique<ProgressReporter>(res->getSize()));
    writer.visitDirectory(*res);

    REQUIRE(false);
}

TEST_CASE("Observer - visit dir3 (with shortcut)", "[Observer]") {
    NullBuffer null_buffer;
    std::ostream null_stream(&null_buffer);

    FollowBuilder builder;

    auto alg = std::make_unique<CryptoPP::SHA256>();
    auto res = builder.buildDir(fs::path(getTestResourcePath("dir3")));
    HashStreamWriter writer(null_stream, std::move(alg));
    writer.subscribe(std::make_unique<ProgressReporter>(res->getSize()));
    writer.visitDirectory(*res);

    REQUIRE(false);
}

TEST_CASE("Observer - visit dir5 (with circular include)", "[Observer]") {
    NullBuffer null_buffer;
    std::ostream null_stream(&null_buffer);

    FollowBuilder builder;

    auto alg = std::make_unique<CryptoPP::SHA256>();
    auto res = builder.buildDir(fs::path(getTestResourcePath("dir5")));
    HashStreamWriter writer(null_stream, std::move(alg));
    writer.subscribe(std::make_unique<ProgressReporter>(res->getSize()));
    writer.visitDirectory(*res);
    
    REQUIRE(false);
}

TEST_CASE("Observer - visit dir7 (With shortcut, single file)", "[Observer]") {
    NullBuffer null_buffer;
    std::ostream null_stream(&null_buffer);

    FollowBuilder builder;

    auto alg = std::make_unique<CryptoPP::SHA256>();
    auto res = builder.buildDir(fs::path(getTestResourcePath("dir7")));
    HashStreamWriter writer(null_stream, std::move(alg));
    writer.subscribe(std::make_unique<ProgressReporter>(res->getSize()));
    writer.visitDirectory(*res);

    REQUIRE(false);
}
