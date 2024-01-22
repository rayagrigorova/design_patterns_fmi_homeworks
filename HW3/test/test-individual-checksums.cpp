#include "catch2/catch_all.hpp"
#include <fstream>
#include <iostream>
#include <filesystem> 
#include <memory>
#include <sstream>
#include <sha.h>
#include <md5.h>
#include <sha3.h>
#include <whrlpool.h>

#include "StrategyChecksumCalculator.h"

namespace fs = std::filesystem;

std::string getTestResourcePath(const std::string& resourceName) {
    fs::path testResourcesPath = fs::current_path().parent_path().parent_path() / "test" / "resources";
    return (testResourcesPath / resourceName).string();
}

TEST_CASE("Hash Calculation Tests", "[StrategyChecksumCalculator]") {
    StrategyChecksumCalculator calculator;
    std::string testData = "Hello, World!";
    std::istringstream iss(testData);

    SECTION("Testing with SHA256 hashing strategy") {
        calculator.setAlgorithm(std::make_unique<CryptoPP::SHA256>());
        std::string result = calculator.calculate(iss);
        REQUIRE(result == "DFFD6021BB2BD5B0AF676290809EC3A53191DD81C7F70A4B28688A362182986F"); 
    }

    SECTION("Testing with SHA1 hashing strategy") {
        calculator.setAlgorithm(std::make_unique<CryptoPP::SHA1>());
        std::string result = calculator.calculate(iss);
        REQUIRE(result == "0A0A9F2A6772942557AB5355D76AF442F8F65E01"); 
    }

    SECTION("Testing with MD5 hashing strategy") {
        calculator.setAlgorithm(std::make_unique<CryptoPP::MD5>());
        std::string result = calculator.calculate(iss);
        REQUIRE(result == "65A8E27D8879283831B664BD8B7F0AD4");
    }

    SECTION("Testing with SHA512 hashing strategy") {
        calculator.setAlgorithm(std::make_unique<CryptoPP::SHA512>());
        std::string result = calculator.calculate(iss);
        REQUIRE(result == "374D794A95CDCFD8B35993185FEF9BA368F160D8DAF432D08BA9F1ED1E5ABE6CC69291E0FA2FE0006A52570EF18C19DEF4E617C33CE52EF0A6E5FBE318CB0387");
    }

    SECTION("Testing with Whirlpool hashing strategy") {
        calculator.setAlgorithm(std::make_unique<CryptoPP::Whirlpool>());
        std::string result = calculator.calculate(iss);
        REQUIRE(result == "3D837C9EF7BB291BD1DCFC05D3004AF2EEB8C631DD6A6C4BA35159B8889DE4B1EC44076CE7A8F7BFA497E4D9DCB7C29337173F78D06791F3C3D9E00CC6017F0B");
    }
}

TEST_CASE("File Hash Calculation Tests", "[StrategyChecksumCalculator]") {
    StrategyChecksumCalculator calculator;
    std::string resourceFileName = "text1.txt";
    std::string filePath = getTestResourcePath(resourceFileName);

    std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
    std::cout << "Attempting to open file: " << filePath << std::endl;

    SECTION("Testing with SHA256 hashing strategy") {
        calculator.setAlgorithm(std::make_unique<CryptoPP::SHA256>());

        std::ifstream fileStream(filePath, std::ios::binary);
        REQUIRE(fileStream.is_open());
        
        std::string result = calculator.calculate(fileStream);
        fileStream.close();

        REQUIRE(result == "31CB5231257471A48C92BE929329E171293501ED09365B236534404AB1730366"); 
    }

    SECTION("Testing with MD5 hashing strategy") {
        calculator.setAlgorithm(std::make_unique<CryptoPP::MD5>());

        std::ifstream fileStream(filePath, std::ios::binary);
        REQUIRE(fileStream.is_open());

        std::string result = calculator.calculate(fileStream);
        fileStream.close();

        REQUIRE(result == "85BE2F4773EE36B77A47F3D6C643CE62");
    }

    SECTION("Testing with SHA1 hashing strategy") {
        calculator.setAlgorithm(std::make_unique<CryptoPP::SHA1>());

        std::ifstream fileStream(filePath, std::ios::binary);
        REQUIRE(fileStream.is_open());

        std::string result = calculator.calculate(fileStream);
        fileStream.close();

        REQUIRE(result == "348F9752A9B2457141A4F864B138728222969B67");
    }
}


TEST_CASE("File Hash Calculation Tests 2", "[StrategyChecksumCalculator]") {
    StrategyChecksumCalculator calculator;
    std::string resourceFileName = "text2.txt";
    std::string filePath = getTestResourcePath(resourceFileName);

    std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
    std::cout << "Attempting to open file: " << filePath << std::endl;

    SECTION("Testing with SHA256 hashing strategy") {
        calculator.setAlgorithm(std::make_unique<CryptoPP::SHA256>());

        std::ifstream fileStream(filePath, std::ios::binary);
        REQUIRE(fileStream.is_open());
        
        std::string result = calculator.calculate(fileStream);
        fileStream.close();

        REQUIRE(result == "3CDB363E5C6A2C7F165C30F3FD7A01C491659BF285E8BFE51A67376A66F418E2"); 
    }

    SECTION("Testing with MD5 hashing strategy") {
        calculator.setAlgorithm(std::make_unique<CryptoPP::MD5>());

        std::ifstream fileStream(filePath, std::ios::binary);
        REQUIRE(fileStream.is_open());

        std::string result = calculator.calculate(fileStream);
        fileStream.close();

        REQUIRE(result == "E89327D074EC50D4A07683B779EB179B");
    }

    SECTION("Testing with SHA1 hashing strategy") {
        calculator.setAlgorithm(std::make_unique<CryptoPP::SHA1>());

        std::ifstream fileStream(filePath, std::ios::binary);
        REQUIRE(fileStream.is_open());

        std::string result = calculator.calculate(fileStream);
        fileStream.close();

        REQUIRE(result == "6A28EB4D0993EB87C38B3A2D52888C0B6208F3EE");
    }
}


TEST_CASE("File Hash Calculation Tests 3", "[StrategyChecksumCalculator]") {
    StrategyChecksumCalculator calculator;
    std::string resourceFileName = "text3.txt";
    std::string filePath = getTestResourcePath(resourceFileName);

    std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
    std::cout << "Attempting to open file: " << filePath << std::endl;

    SECTION("Testing with SHA256 hashing strategy") {
        calculator.setAlgorithm(std::make_unique<CryptoPP::SHA256>());

        std::ifstream fileStream(filePath, std::ios::binary);
        REQUIRE(fileStream.is_open());
        
        std::string result = calculator.calculate(fileStream);
        fileStream.close();

        REQUIRE(result == "E3AF6A719FC59642C805FF71F21410E8E3EA1A5D893DA469A58B68C7EC44565F"); 
    }

    SECTION("Testing with MD5 hashing strategy") {
        calculator.setAlgorithm(std::make_unique<CryptoPP::MD5>());

        std::ifstream fileStream(filePath, std::ios::binary);
        REQUIRE(fileStream.is_open());

        std::string result = calculator.calculate(fileStream);
        fileStream.close();

        REQUIRE(result == "8749ADF69A1534F13E9589B2D3DA5EA7");
    }

    SECTION("Testing with SHA1 hashing strategy") {
        calculator.setAlgorithm(std::make_unique<CryptoPP::SHA1>());

        std::ifstream fileStream(filePath, std::ios::binary);
        REQUIRE(fileStream.is_open());

        std::string result = calculator.calculate(fileStream);
        fileStream.close();

        REQUIRE(result == "535AE6587A7D73C9B0E3609E0C3E1A1C09683690");
    }
}


TEST_CASE("File Hash Calculation For Empty File", "[StrategyChecksumCalculator]") {
    StrategyChecksumCalculator calculator;
    std::string resourceFileName = "text4.txt";
    std::string filePath = getTestResourcePath(resourceFileName);

    std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;
    std::cout << "Attempting to open file: " << filePath << std::endl;

    SECTION("Testing with SHA256 hashing strategy") {
        calculator.setAlgorithm(std::make_unique<CryptoPP::SHA256>());

        std::ifstream fileStream(filePath, std::ios::binary);
        REQUIRE(fileStream.is_open());
        
        std::string result = calculator.calculate(fileStream);
        fileStream.close();

        REQUIRE(result == "E3B0C44298FC1C149AFBF4C8996FB92427AE41E4649B934CA495991B7852B855"); 
    }

    SECTION("Testing with MD5 hashing strategy") {
        calculator.setAlgorithm(std::make_unique<CryptoPP::MD5>());

        std::ifstream fileStream(filePath, std::ios::binary);
        REQUIRE(fileStream.is_open());

        std::string result = calculator.calculate(fileStream);
        fileStream.close();

        REQUIRE(result == "D41D8CD98F00B204E9800998ECF8427E");
    }

    SECTION("Testing with SHA1 hashing strategy") {
        calculator.setAlgorithm(std::make_unique<CryptoPP::SHA1>());

        std::ifstream fileStream(filePath, std::ios::binary);
        REQUIRE(fileStream.is_open());

        std::string result = calculator.calculate(fileStream);
        fileStream.close();

        REQUIRE(result == "DA39A3EE5E6B4B0D3255BFEF95601890AFD80709");
    }
}
