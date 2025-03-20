#include "CSVHandler.h"
#include "algorithms/trivial_algo.h"
#include "validator.h"
#include <filesystem>
#include <iostream>
#include <vector>

namespace fs = std::filesystem;

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
 * @brief Requests user to select a CSV file to process.
 *
 * @return std::string Path (relative to executable) to the selected CSV file.
 */
std::string requestFileName() {
  const std::string start_directory = "data";
  std::vector<std::string> csv_files;

  // Check if the directory exists
  if (!fs::exists(start_directory) || !fs::is_directory(start_directory)) {
    throw std::runtime_error("Directory '" + start_directory +
                             "' does not exist or is not a directory.");
  }

  // Gather CSV files
  for (const auto &entry : fs::directory_iterator(start_directory)) {
    if (entry.is_regular_file() && entry.path().extension() == ".csv") {
      csv_files.push_back(entry.path().filename().string());
    }
  }

  // Check if any CSV files were found
  if (csv_files.empty()) {
    throw std::runtime_error("No CSV files found in the directory.");
  }

  // Display the list of CSV files
  std::cout << "Available CSV files:\n";
  for (size_t i = 0; i < csv_files.size(); ++i) {
    std::cout << i + 1 << ". " << csv_files[i] << "\n";
  }

  // User selection
  size_t choice;
  std::cout << "Enter the number of the file you want to select: ";
  std::cin >> choice;

  if (choice < 1 || choice > csv_files.size()) {
    throw std::runtime_error("Invalid selection.");
  }

  return start_directory + "/" + csv_files[choice - 1];
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
  const std::string output_filename = "output.csv";

  std::string input_filename = "../data/mini.csv";
  int columnCount = 4; // number of columns to be clustered
  bool forwardPass = true;

  // Prompt user for input
  input_filename = requestFileName();

  std::cout
      << "Do you want to perform a forward pass (1) or backward pass (0)? ";
  std::cin >> forwardPass;

  std::cout << "Enter the number of columns to be clustered: ";
  std::cin >> columnCount;

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
  std::cout << "Processing..." << std::endl;
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
