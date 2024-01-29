#include <iostream>
#include <streambuf>

class NullBuffer : public std::streambuf {
public:
    int overflow(int c) override;
};

std::string getTestResourcePath(const std::string& resourceName);



