#include "CSVHandler.h"
#include "algorithms/trivial_algo.h"
#include "validator.h"
#include <iostream>

/**
 * @brief Workflow for main program that compresses an input CSV. The output is
 * saved to output.csv.
 *
 */
void mainWorkflow() {
  std::string input_filename;
  const std::string output_filename = "output.csv";

  // Prompt the user to input the file names
  std::cout << "Enter the input file name (e.g., input.csv): ";
  std::cin >> input_filename;

  // Validating CSV
  auto csv_validation = CSVHandler::isValidCSV(input_filename);
  if (!csv_validation.first) {
    std::cerr << "Validation Error: " << csv_validation.second << std::endl;
    return;
  }

  // Reading from CSV
  std::string csvContent = CSVHandler::readCSVAsString(input_filename);

  // Compress CSV
  TrivialAlgorithm algo;
  std::string output = algo.solve(csvContent);
  std::cout << output << std::endl;

  // Validate output
  auto validation = Validator::validate_output(csvContent, output);
  std::cout << "Output validation: " << validation.second << std::endl;

  // Writing to CSV
  if (CSVHandler::writeToFile(output_filename, output)) {
    std::cout << "Data written to " << output_filename << std::endl;
  }
}

/**
 * @brief Workflow for the first task assigned:
 *
 * User should be able to do clustering for 1, 2, 3, 4, ... columns in any order
 * we want - i.e. starting with the first then second then third or last then
 * one before last etc..
 *
 */
void clusterExerciseWorkflow() {
  std::string input_filename = "../data/3k_5.csv";
  int columnCount = 4; // number of columns to be clustered
  bool forwardPass = true;

  const std::string output_filename = "output.csv";

  // Prompt user for input
  std::cout
      << "Enter the input file name (e.g., input.csv) in the data folder: ";
  std::cin >> input_filename;

  input_filename = "../data/" + input_filename;

  std::cout << "Enter the number of columns to be clustered: ";
  std::cin >> columnCount;

  std::cout
      << "Do you want to perform a forward pass (1) or backward pass (0)? ";
  std::cin >> forwardPass;

  // Validating CSV
  auto csv_validation = CSVHandler::isValidCSV(input_filename);
  if (!csv_validation.first) {
    std::cerr << "Validation Error: " << csv_validation.second << std::endl;
    return;
  }

  // Reading from CSV
  std::vector<std::vector<std::string>> csvContentAsVector =
      CSVHandler::readCSVAsVector(input_filename);

  // Perform clustering
  std::string output = TrivialAlgorithm::clusterByColumns(
      csvContentAsVector, columnCount, forwardPass);

  // Writing to CSV
  if (CSVHandler::writeToFile(output_filename, output)) {
    std::cout << "Data written to " << output_filename << std::endl;
  }

  // Validate output
  std::string csvContentAsString = CSVHandler::readCSVAsString(input_filename);
  auto validation = Validator::validate_output(csvContentAsString, output);
  std::cout << "Output validation: " << validation.second << std::endl;
}

int main() {
  clusterExerciseWorkflow();
  return 0;
}
