/**
 * @file validator_main.cpp
 * @brief Main entry point for the validator program.
 *
 * This program is responsible for checking the validity of an input file
 * and its corresponding output file.
 *
 */

#include "CSVHandler.h"
#include "validator.h"

#include <iostream>
#include <limits>
#include <vector>

int main() {
  std::string input_path;
  std::string output_path;

  // prompt user for input
  std::cout << "Enter path to input file: ";
  std::cin >> input_path;

  std::cout << "Enter path to output file: ";
  std::cin >> output_path;

  // read input and output files
  std::string input = CSVHandler::readCSVAsString(input_path);
  std::string output = CSVHandler::readCSVAsString(output_path);

  // validate input file
  auto input_csv_validation = CSVHandler::isValidCSV(input_path);

  if (input_csv_validation.first) {
    std::cout << "√ Input valid" << std::endl;

    // validate output against input
    auto output_validation = Validator::validate_output(input, output);
    if (output_validation.first) {
      std::cout << "√ Output valid" << std::endl;
    } else {
      std::cout << "Х Output invalid" << std::endl;
      std::cout << output_validation.second << std::endl;
    }
  } else {
    std::cout << "Х Input invalid" << std::endl;
    std::cout << input_csv_validation.second << std::endl;
  }

  // wait for user input to close terminal
  std::cout << std::endl << "Press Enter to exit..." << std::endl;
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
  std::cin.get();

  return 0;
}