#include <iostream>
#include <string>
#include <sha.h>
#include <hex.h>

using namespace CryptoPP;

std::string SHA256HashString(const std::string& input) {
    CryptoPP::SHA256 hash;
    byte digest[CryptoPP::SHA256::DIGESTSIZE];

    hash.CalculateDigest(digest, reinterpret_cast<const byte*>(input.c_str()), input.length());

    CryptoPP::HexEncoder encoder;
    std::string output;
    encoder.Attach(new CryptoPP::StringSink(output));
    encoder.Put(digest, sizeof(digest));
    encoder.MessageEnd();

    return output;
}

int main() {
    std::string message = "Hello, Crypto++!";
    std::string digest = SHA256HashString(message);

    std::cout << "Message: " << message << std::endl;
    std::cout << "SHA-256 Digest: " << digest << std::endl;

    return 0;
}
