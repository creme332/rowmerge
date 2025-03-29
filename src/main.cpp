#include "CSVHandler.h"
#include "algorithms/CompressedTableAlgo.h"
#include "validator.h"
#include <iostream>
#include <limits>
#include <vector>
#ifdef _MSC_VER
    #include <filesystem>
    namespace fs = std::filesystem;
#else
    #include <experimental/filesystem>
    namespace fs = std::experimental::filesystem;
#endif

void mainWorkflow() {
    std::string input_filename;
    const std::string output_filename = "output.csv";

    std::cout << "Enter the input file name (e.g., input.csv): ";
    std::cin >> input_filename;

    auto csv_validation = CSVHandler::isValidCSV(input_filename);
    if (!csv_validation.first) {
        std::cerr << "Validation Error: " << csv_validation.second << std::endl;
        return;
    }

    std::string csvContent = CSVHandler::readCSVAsString(input_filename);

    CompressedTableAlgorithm algo;
    std::string output = algo.solve(csvContent);
    std::cout << output << std::endl;

    auto validation = Validator::validate_output(csvContent, output);
    std::cout << "Output validation: " << validation.second << std::endl;

    if (CSVHandler::writeToFile(output_filename, output)) {
        std::cout << "Data written to " << output_filename << std::endl;
    }
}

int main() {
    mainWorkflow();
    return 0;
}