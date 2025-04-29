#include "CSVHandler.h"
#include "algorithms/new_algo.h"
#include "algorithms/optimized_algo.h"
#include "algorithms/trivial_algo.h"
#include "timer.h"
#include "validator.h"
#include <filesystem>
#include <iostream>
#include <limits>
#include <vector>

namespace fs = std::filesystem;

/**
 * @brief Requests user to enter an integer. If user enters an invalid integer,
 * he is repeatedly shown the prompt and asked to enter a valid one.
 *
 * @param prompt Message shown to user when requesting input
 * @return int Integer value entered by user
 */
int requestInteger(const std::string &prompt) {
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
  std::string prompt = "Enter the number (1-" +
                       std::to_string(csv_files.size()) +
                       ") of the file you want to select: ";
  size_t choice;
  do {
    choice = requestInteger(prompt);
  } while (choice < 1 || choice > csv_files.size());

  return csv_files[choice - 1];
}

/**
 * @brief Counts the number of newlines in a string.
 *
 * @param str String with newlines
 * @return int
 */
int countRows(const std::string &str) {
  int rowCount = 0;

  // Count the number of newlines in the string
  for (char ch : str) {
    if (ch == '\n') {
      ++rowCount;
    }
  }

  return rowCount;
}

/**
 * @brief Waits for any input, clearing the buffer and waiting for the user to
 * press any key. Use this function to avoid closing terminal immediately when
 * program ends. This gives user time to view output.
 *
 */
void endProgram() {
  std::cout << "\nPress Enter to exit..." << std::flush;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(),
                  '\n'); // Clear input buffer
  std::cin.get();        // Wait for user input
  exit(EXIT_SUCCESS);
}

/**
 * @brief Program for first 3 tasks assigned from `docs/PROBLEM_STATEMENT.md`.
 *
 */
void mainProgram() {
  std::string start_directory = "data/"; // directory containing input CSV files

  // initialize start directory. If no data directory found, look one level up
  if (!fs::exists(start_directory) || !fs::is_directory(start_directory)) {
    start_directory = "../data/";

    // If data directory still missing, end program
    if (!fs::exists(start_directory) || !fs::is_directory(start_directory)) {
      std::cerr << "Missing data folder! Create a folder 'data' in the current "
                   "directory"
                << std::endl;
      endProgram();
    }
  }

  // Prompt user for file input
  const std::string input_filename = requestFileName(start_directory);
  const std::string input_filepath = start_directory + input_filename;

  // Reading from CSV
  std::vector<std::vector<std::string>> csvContentAsVector =
      CSVHandler::readCSVAsVector(input_filepath);

  // Validate input file
  auto input_csv_validation = CSVHandler::isValidCSV(input_filepath);
  if (!input_csv_validation.first) {
    std::cerr << "! " + input_filename + " is invalid: "
              << input_csv_validation.second << std::endl;
    endProgram();
  }

  // Print details of input file
  const int initialRowCount = csvContentAsVector.size();
  const int initialColCount = csvContentAsVector[0].size();

  std::cout << "+ " + input_filename + " is valid. It has " +
                   std::to_string(initialRowCount) + " rows and " +
                   std::to_string(initialColCount) + " columns.\n\n";

  // define parameters of algorithm
  int modeNumber = 1;      // method chosen by user
  int columnCount = 5;     // number of columns to be clustered
  int startColumn = 0;     // index of column where clustering will begin
  bool forwardPass = true; // direction of processing
  int tolerance = 1;

  // request method

  std::cout << "Available clustering modes:\n"
            << "  0 - Selective clustering\n"
            << "      * User-defined parameters\n"
            << "  1 - Normal clustering\n"
            << "      * Automatically determined parameters\n"
            << "  2 - Normal clustering with row repetition\n"
            << "      * Automatically determined parameters\n"
            << "      * Row repetition allowed\n\n";

  do {
    modeNumber = requestInteger("Choose method (0, 1, or 2): ");
  } while (modeNumber < 0 || modeNumber > 2);

  // if selective clustering has been selected, request more info from user
  if (modeNumber == 0) {
    // prompt for tolerance level
    do {
      tolerance = requestInteger("Enter euclidean distance (1-3): ");
    } while (tolerance < 1 || tolerance > 3);

    // prompt for additional details if tolerance is 1
    if (tolerance == 1) {
      // prompt for clustering details
      int input;
      do {
        input = requestInteger(
            "Choose pass direction (1 = Forward, 0 = Backward): ");
        forwardPass = input;
      } while (input != 1 && input != 0);

      std::cout << "Enter clustering details:\n";

      // request startColumn
      do {
        startColumn =
            requestInteger("  - Start column index (0-" +
                           std::to_string(initialColCount - 1) + "): ");
      } while (startColumn < 0 || startColumn >= initialColCount);

      // request columnCount
      do {
        columnCount =
            requestInteger("  - Number of columns (1-" +
                           std::to_string(initialColCount) + ") to cluster: ");
      } while (columnCount < 1 || columnCount > initialColCount);
    }
  }

  // Perform clustering and start a timer
  TrivialAlgorithm algo;
  std::string output;
  std::cout << std::endl
            << "Processing " << input_filename << "..." << std::endl;

  Timer timer;
  timer.start();
  try {
    if (modeNumber == 0) {
      // selective clustering mode
      if (tolerance == 1) {
        output = algo.clusterByColumns(csvContentAsVector, startColumn,
                                       columnCount, forwardPass);
      } else {
        // non-default tolerance
        output = algo.clusterWithTolerance(csvContentAsVector, tolerance);
      }
    } else if (modeNumber == 1) {
      // normal clustering
      output = algo.solve(csvContentAsVector);
    } else {
      // normal clustering with row repetition
      output = algo.clusterWithRowDuplication(csvContentAsVector);
    }
  } catch (std::exception e) {
    std::cerr << e.what() << std::endl;
    timer.stop();
    endProgram();
  }

  timer.stop();

  std::cout << "\n--- Statistics ---\n";

  // print time
  timer.printElapsedTime();

  // Calculate compression ratio

  // Avoid division by zero in case initialRowCount is 0
  if (initialRowCount != 0) {
    const int finalRowCount = countRows(output);
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

  // Validate output if tolerance is default = 1 or normal clustering mode is
  // used
  if (modeNumber == 1 || (tolerance == 1 && modeNumber == 0)) {
    std::cout << "Validating output..." << std::endl;
    std::string csvContentAsString = CSVHandler::readFile(input_filepath);
    auto validation = Validator::validate_output(csvContentAsString, output);
    std::cout << "Result: " << validation.second << std::endl;
  }

  endProgram();
}

/**
 * @brief Programs that runs a single algorithm without requesting user for
 * input other than the input file.
 *
 */
void runAlgorithm() {
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
  TrivialAlgorithm algo;

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
  std::string csvContentAsString = CSVHandler::readFile(input_filepath);
  auto validation = Validator::validate_output(csvContentAsString, output);
  std::cout << "Result: " << validation.second << std::endl;
}

/**
 * @brief Tests an algorithm against data in `data` folder and outputs
 * statistics.
 *
 * @param algo Algorithm being tested.
 */
void benchmarkAlgorithm(AlgorithmBase &algo) {
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
    std::string csvContentAsString = CSVHandler::readFile(input_filepath);
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

int main() { mainProgram(); }