#include <iostream>
#include <thread> 
#include <typeinfo>

#include "ProgressReporter.h"
#include "HashStreamWriter.h"

const size_t SLEEP_TIME = 100;
const size_t PERCENTAGE_STEP = 10;
const char PERCENTAGE_CHAR = '#';

// The ProgressReporter is initialized with the total number of bytes of a file/directory 
ProgressReporter::ProgressReporter(std::uintmax_t totalBytes) : totalBytes(totalBytes){
    // Start tracking the elapsed time as soon as the ProgressReporter is initialized with a directory/file
    startTime = std::chrono::steady_clock::now();
}

namespace {
    void visualizePercentage(double percentage) {
        if (percentage < 0) {
            std::cerr << "The number representing the file processing percentage is invalid\n";
            return;
        }
        std::cout << "\r";

        double copyPercentage = percentage; 
        int number_of_symbols = ceil(100.0 / PERCENTAGE_STEP);

        for (int i = 0; i < number_of_symbols; i++) {
            if (percentage >= PERCENTAGE_STEP) {
                std::cout << PERCENTAGE_CHAR;
            }
            else {
                std::cout << " ";
            }
            percentage -= PERCENTAGE_STEP;
        }

        std::cout << " " << std::fixed << std::setprecision(2) << copyPercentage << "%";
    }
}

void ProgressReporter::update(const Observable& sender, const std::string& context) {
    if (typeid(sender) == typeid(HashStreamWriter)) {
        std::cout << "\nProcessing " << context << "...\n";
    }
    else if (typeid(sender) == typeid(StrategyChecksumCalculator)) {
        try {
            std::uintmax_t conversionResult = std::stoull(context);
            bytesProcessed += conversionResult;
        }
        catch (const std::exception& e) {
            std::cerr << "\nError in string to number conversion: " << e.what() << "\n";
        }

        double percentage = (totalBytes == 0) ? 0 : ((double)bytesProcessed / totalBytes) * 100;
        std::chrono::time_point<std::chrono::steady_clock> currentTime = std::chrono::steady_clock::now();
        std::chrono::milliseconds::rep elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count();
        double processingSpeed = (elapsed == 0) ? 0 : (double)bytesProcessed / elapsed;
        double timeRemaining = (processingSpeed < std::numeric_limits<double>::epsilon()) ? 0 : (totalBytes - bytesProcessed) / processingSpeed;

        std::cout << "\r" << context << " byte(s) read ";
        visualizePercentage(percentage);
        std::cout << " Time remaining (seconds): " << std::fixed << std::setprecision(5) <<  timeRemaining / 1000;
        std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME));
    }
}

