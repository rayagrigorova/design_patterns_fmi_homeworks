#include "StrategyChecksumCalculator.h"

#include <hex.h>
#include <filters.h>

const size_t BUFFER_SIZE = 4096; // a buffer size of 4KB; 
// The size is chosen so that the I/O operations are not too frequent and in order not to waste memory. 

StrategyChecksumCalculator::StrategyChecksumCalculator(std::unique_ptr<CryptoPP::HashTransformation>&& strategy)
    : strategy(std::move(strategy)){
}

// !!!!!  
// The implementation of the function below partly relies on help by OpenAI's ChatGPT 
// (more specifically the parts related to the usage of the CryptoPP library to hash a string)
std::string StrategyChecksumCalculator::calculate(std::istream& is) const {
    if (!strategy) {
        std::cerr << "Hashing strategy not set." << std::endl;
        return "";
    }

    std::string output; // This string will be used to store the final hash 

    // The 'hex encoder' converts the binary data to a hexadecimal string
    // 'StringSink' will write hexadecimal output to the 'output' string.
    CryptoPP::HexEncoder encoder(new CryptoPP::StringSink(output));

    // 'hashFilter' uses 'strategy' to hash the data and passes the hashed output to 'encoder'
    CryptoPP::HashFilter hashFilter(*strategy, new CryptoPP::Redirector(encoder));

    char buffer[BUFFER_SIZE];
    std::uintmax_t processed = 0;

    // If some error state flag is set to true(including eofbit), good() will return false 
    while (is.good()) {
        // Read the data as binary 
        is.read(buffer, sizeof(buffer));

        // The function gcount() will return the number of characters extracted
        // by the last unformatted input operation
        std::streamsize count = is.gcount();
        processed += count;

        // Notify subscribers about the newly processed data 
        notifySubscribers(std::to_string(count));

        // If any information was read, add it to the buffer that manages the hash computation 
        if (count > 0) {
            hashFilter.Put(reinterpret_cast<const CryptoPP::byte*>(buffer), static_cast<size_t>(count));
        }
    }
    // This finalizes the hash calculation
    hashFilter.MessageEnd();

    return output;
}

void StrategyChecksumCalculator::setAlgorithm(std::unique_ptr<CryptoPP::HashTransformation>&& newStrategy) {
    strategy = std::move(newStrategy);
}
