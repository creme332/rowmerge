#include "CSVHandler.h"
#include "algorithms/trivial_algo.h"
#include "validator.h"
#include <filesystem>
#include <iostream>
#include <limits>
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
 * @param start_directory Path to directory where CSV files are found. A
 * trailing slash must be present. E.g.
 * `../data/`
 * @return std::string Filename of CSV file selected
 */
std::string requestFileName(const std::string start_directory) {
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
    std::cout << "  " << i + 1 << ". " << csv_files[i] << "\n";
  }

  std::cout << std::endl;

  // User selection
  size_t choice = -1;
  while (choice < 1 || choice > csv_files.size()) {
    std::cout << "Enter the number of the file you want to select: ";
    std::cin >> choice;
  }

  return csv_files[choice - 1];
}

int getValidatedInt(const std::string &prompt) {
  int value;
  while (true) {
    std::cout << prompt;
    std::cin >> value;

    if (std::cin.fail()) {
      std::cin.clear(); // Clear error flag
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                      '\n'); // Discard input
      std::cout << "Invalid input! Please enter a valid number.\n";
    } else {
      break; // Valid input
    }
  }
  return value;
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
  const std::string start_directory = "data/";
  int columnCount = 4; // number of columns to be clustered
  int startColumn = 1;
  bool forwardPass = true;

  // Prompt user for input
  std::string input_filename = requestFileName(start_directory);

  // Determine path to input file
  std::string input_filepath = start_directory + input_filename;

  do {
    std::cout << "Choose pass direction (1 = Forward, 0 = Backward): ";
    std::cin >> forwardPass;

    if (std::cin.fail() || (forwardPass != 0 && forwardPass != 1)) {
      std::cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      std::cout << "Invalid choice! Please enter 0 or 1.\n";
    } else {
      break;
    }
  } while (true);

  std::cout << "Enter clustering details:\n";
  startColumn = getValidatedInt("  - Start column index (zero-based): ");
  columnCount = getValidatedInt("  - Number of columns to cluster: ");

  // Validating CSV
  auto csv_validation = CSVHandler::isValidCSV(input_filepath);
  if (!csv_validation.first) {
    std::cerr << "Validation Error: " << csv_validation.second << std::endl;
    return;
  }

  // Reading from CSV
  std::vector<std::vector<std::string>> csvContentAsVector =
      CSVHandler::readCSVAsVector(input_filepath);

  // Perform clustering
  std::cout << std::endl << "Processing..." << std::endl;
  std::string output = TrivialAlgorithm::clusterByColumns(
      csvContentAsVector, startColumn, columnCount, forwardPass);

  // Create folder for output
  fs::create_directory("output");
  std::string output_filename = "output/" + input_filename;

  // Writing to CSV
  if (CSVHandler::writeToFile(output_filename, output)) {
    std::cout << "Processing over. Data written to " << output_filename
              << std::endl;
  }

  // Validate output
  std::cout << "Validating output..." << std::endl;
  std::string csvContentAsString = CSVHandler::readCSVAsString(input_filepath);
  auto validation = Validator::validate_output(csvContentAsString, output);
  std::cout << "Result: " << validation.second << std::endl;

  std::cout << "Press Enter to exit..." << std::endl;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                  '\n'); // Clear input buffer
  std::cin.get();        // Wait for user input
}

int main() {
  clusterExerciseWorkflow();
  return 0;
}