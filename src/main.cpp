#include "CSVHandler.h"
#include "algorithms/sample_algo.h"
#include "validator.h"
#include <iostream>

int main() {
  const std::string input_filename = "data.csv";
  const std::string output_filename = "output.csv";

  // Validating CSV
  auto csv_validation = CSVHandler::isValidCSV(input_filename);
  if (csv_validation.first) {
    std::cout << "CSV file is valid!" << std::endl;
  } else {
    std::cerr << "Validation Error: " << csv_validation.second << std::endl;
    return 0;
  }

  // Reading from CSV
  std::string csvContent = CSVHandler::readCSV(input_filename);

  // Compress CSV
  SampleAlgorithm algo;
  std::string output = algo.solve(csvContent);

  auto validation = Validator::validate_output(csvContent, output);
  std::cout << "Output validation: " << validation.second << std::endl;

  // Writing to CSV
  if (CSVHandler::writeToFile(output_filename, output)) {
    std::cout << "Data written to " << output_filename << std::endl;
  }

  return 0;
}
