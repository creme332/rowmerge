#include "CSVHandler.h"
#include "algorithms/new_algo.h"
#include "algorithms/optimized_algo.h"
#include "algorithms/trivial_algo.h"

#include "timer.h"
#include "validator.h"
#include <iostream>
#include <limits>
#include <vector>

namespace fs = std::filesystem;

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

int countRows(const std::string &str) {
  int rowCount = 0;

  // Count the number of pipes in the string
  for (char ch : str) {
    if (ch == '\n') {
      ++rowCount;
    }
  }

  return rowCount;
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
  std::string start_directory = "data/";
  int columnCount = 5; // number of columns to be clustered
  int startColumn = 0;
  bool forwardPass = true;

  // initialize start directory. If no data directory found, look one level up
  if (!fs::exists(start_directory) || !fs::is_directory(start_directory)) {
    start_directory = "../data/";
  }

  // Prompt user for file input
  std::string input_filename = requestFileName(start_directory);
  std::string input_filepath = start_directory + input_filename;

  // Reading from CSV
  std::vector<std::vector<std::string>> csvContentAsVector =
      CSVHandler::readCSVAsVector(input_filepath);

  // Validate input file
  auto input_csv_validation = CSVHandler::isValidCSV(input_filepath);
  if (!input_csv_validation.first) {
    std::cerr << "❌ " + input_filename + " is invalid: "
              << input_csv_validation.second << std::endl;
    return;
  }

  std::cout << "✅ " + input_filename + " is valid." << std::endl;

  // prompt for tolerance level
  int tolerance = getValidatedInt("Enter euclidean distance (1-3): ");

  // prompt for additional details if tolerance is 1
  if (tolerance == 1) {
    // prompt for clustering details
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
  }

  // Perform clustering
  TrivialAlgorithm algo;
  std::string output;
  std::cout << std::endl
            << "Processing " << input_filename << "..." << std::endl;
  Timer timer;
  timer.start();
  if (tolerance == 1) {
    output = algo.clusterByColumns(csvContentAsVector, startColumn, columnCount,
                                   forwardPass);
  } else {
    output = algo.clusterWithTolerance(csvContentAsVector, tolerance);
  }
  timer.stop();

  std::cout << "\n--- Statistics ---\n";
  // print time
  timer.printElapsedTime();

  // Calculate compression ratio
  const int initialRowCount = csvContentAsVector.size();
  const int finalRowCount = countRows(output);

  // Avoid division by zero in case initialRowCount is 0
  if (initialRowCount != 0) {
    double compressionRatio =
        static_cast<double>(finalRowCount) / initialRowCount;
    std::cout << "Compression ratio = " << compressionRatio
              << " (smaller = better)" << std::endl;
  } else {
    std::cout
        << "Initial row count is 0, compression ratio cannot be calculated."
        << std::endl;
  }
  std::cout << "------------------\n\n";

  // Create folder for output
  fs::create_directory("output");
  std::string output_filename = "output/" + input_filename;

  // Writing to CSV
  if (CSVHandler::writeToFile(output_filename, output)) {
    std::cout << "Output written to " << output_filename << std::endl;
  }

  // Validate output
  std::cout << "Validating output..." << std::endl;
  std::string csvContentAsString = CSVHandler::readCSVAsString(input_filepath);
  auto validation = Validator::validate_output(csvContentAsString, output);
  std::cout << "Result: " << validation.second << std::endl;

  std::cout << std::endl << "Press Enter to exit..." << std::endl;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                  '\n'); // Clear input buffer
  std::cin.get();        // Wait for user input
}

/**
 * @brief Workflow for main program that compresses an input CSV.
 *
 */
void mainWorkflow() {
  std::string start_directory = "data/";

  // initialize start directory. If no data directory found, look one level up
  if (!fs::exists(start_directory) || !fs::is_directory(start_directory)) {
    start_directory = "../data/";
  }

  // Prompt user for input
  std::string input_filename = requestFileName(start_directory);

  // Determine path to input file
  std::string input_filepath = start_directory + input_filename;

  // Validate input file
  std::cout << "Validating input file..." << std::endl;
  auto input_csv_validation = CSVHandler::isValidCSV(input_filepath);
  if (!input_csv_validation.first) {
    std::cerr << "Input CSV Error: " << input_csv_validation.second
              << std::endl;
    return;
  }
  std::cout << "Input valid." << std::endl;

  // Reading from CSV
  std::vector<std::vector<std::string>> csvContentAsVector =
      CSVHandler::readCSVAsVector(input_filepath);

  // Perform clustering
  OptimizedAlgorithm algo;

  Timer timer;
  std::cout << std::endl << "Processing..." << std::endl;

  timer.start();
  std::string output = algo.solve(csvContentAsVector);
  timer.stop();

  timer.printElapsedTime();

  // Calculate compression ratio
  const int initialRowCount = csvContentAsVector.size();
  const int finalRowCount = countRows(output);

  // Avoid division by zero in case initialRowCount is 0
  if (initialRowCount != 0) {
    double compressionRatio =
        static_cast<double>(finalRowCount) / initialRowCount;
    std::cout << "Compression ratio = " << compressionRatio << std::endl;
  } else {
    std::cout
        << "Initial row count is 0, compression ratio cannot be calculated."
        << std::endl;
  }

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
}

/**
 * @brief Tests an algorithm against data in `data` folder and outputs
 * statistics.
 *
 * @param algo Algorithm being tested.
 */
void testAlgorithm(AlgorithmBase &algo) {
  std::string start_directory = "../data/";
  Timer timer;

  // Loop through each CSV files for testing
  for (const auto &entry : fs::directory_iterator(start_directory)) {
    // ignore non-csv files
    if (!entry.is_regular_file() || entry.path().extension() != ".csv")
      continue;

    // construct path to csv file
    std::string input_filepath =
        start_directory + entry.path().filename().string();

    std::cout << input_filepath << std::endl;

    // convert csv to vector
    std::vector<std::vector<std::string>> csvContentAsVector =
        CSVHandler::readCSVAsVector(input_filepath);

    const int initialRowCount = csvContentAsVector.size();

    // time algorithm
    timer.reset();
    timer.start();
    std::string output = algo.solve(csvContentAsVector);
    timer.stop();

    // Validate output
    std::string csvContentAsString =
        CSVHandler::readCSVAsString(input_filepath);
    auto validation = Validator::validate_output(csvContentAsString, output);
    std::cout << "Result: " << validation.second << std::endl;

    const int finalRowCount = countRows(output);

    timer.printElapsedTime();

    double compressionRatio =
        static_cast<double>(finalRowCount) / initialRowCount;
    std::cout << "Compression ratio = " << compressionRatio << std::endl;
    std::cout << std::endl;
  }
}

int main() { clusterExerciseWorkflow(); }