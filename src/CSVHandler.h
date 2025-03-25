#ifndef CSV_HANDLER_H
#define CSV_HANDLER_H

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <sys/stat.h> // For checking file existence and size
#include <utility>    // For std::pair
#include <vector>

/**
 * @class CSVHandler
 * @brief A utility class for handling CSV file operations, including reading,
 * writing, and validation.
 */
class CSVHandler {
public:
  /**
   * @brief Reads the entire content of a CSV file and returns it as a string.
   *
   * @param filename The name of the CSV file to read.
   * @return std::string The content of the CSV file. Returns an empty string if
   * an error occurs.
   */
  static std::string readCSVAsString(const std::string &filename);

  /**
   * @brief Reads a CSV file and parses its contents into a vector of rows,
   *        where each row is represented as a vector of strings (columns).
   *
   * @param filename The path to the CSV file.
   * @return A vector of rows, where each row is a vector of strings
   * representing the columns.
   * @throws std::runtime_error If the file cannot be opened.
   *
   * @note This function assumes that the CSV file uses commas (`,`) as the
   * delimiter. It does not handle quoted values or escape characters.
   */
  static std::vector<std::vector<std::string>>
  readCSVAsVector(const std::string &filename);

  /**
   * @brief Writes a string content to a specified file.
   *
   * @param filename The name of the file to write to.
   * @param content The string content to be written to the file.
   * @return true If the file is successfully written.
   * @return false If the file could not be written.
   */
  static bool writeToFile(const std::string &filename,
                          const std::string &content);

  /**
   * @brief Validates a CSV file by checking if it has a `.csv` extension,
   * exists, and is not empty.
   *
   * @param filename The name of the CSV file to validate.
   * @return std::pair<bool, std::string>
   *         - `first` (bool): True if valid, false otherwise.
   *         - `second` (std::string): An error message if invalid, or "File is
   * valid." if valid.
   */
  static std::pair<bool, std::string> isValidCSV(const std::string &filename);
};

#endif // CSV_HANDLER_H
