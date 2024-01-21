#include "StrategyChecksumCalculator.h"

#include <hex.h>
#include <filters.h>

const size_t BUFFER_SIZE = 4096; // a buffer size of 4KB; 
// The size is chosen so that the I/O operations are not too frequent and 
// and in order not to waste memory. 

StrategyChecksumCalculator::StrategyChecksumCalculator(std::unique_ptr<CryptoPP::HashTransformation>&& strategy)
    : strategy(std::move(strategy)){

}

std::string StrategyChecksumCalculator::calculate(std::istream& is) const {
    if (!strategy) {
        std::cerr << "Hashing strategy not set.\n";
        return "";
    }

    std::string output; // this string will be used to store the final hash 
    // The 'hex encoder' converts the binary data to a hexadecimal string
    // 'StringSink' will write hexadecimal output to the 'output' string.
    CryptoPP::HexEncoder encoder(new CryptoPP::StringSink(output));
    // 'hashFilter' uses 'strategy' to hash the data and passes the hashed output to 'encoder'
    CryptoPP::HashFilter hashFilter(*strategy, new CryptoPP::Redirector(encoder));

    char buffer[BUFFER_SIZE];

    // If some error state flag is set to true(including eofbit),
    // good() will return false 
    while (is.good()) {
        // read the data as binary 
        is.read(buffer, sizeof(buffer));

        // the function gcount() will return  the number of characters extracted
        // by the last unformatted input operation
        std::streamsize count = is.gcount();
        if (count > 0) {
            // process 'buffer' as a CryptoPP::byte buffer
            // 'count' is the size of the data read from 'is' (in bytes)
            hashFilter.Put(reinterpret_cast<const CryptoPP::byte*>(buffer), static_cast<size_t>(count));
        }
    }
    // this finalizes the hash calculation
    hashFilter.MessageEnd();

    return output;
}

void StrategyChecksumCalculator::setAlgorithm(std::unique_ptr<CryptoPP::HashTransformation>&& newStrategy) {
    strategy = std::move(newStrategy);
}
