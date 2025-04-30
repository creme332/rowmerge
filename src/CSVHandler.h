#ifndef CSV_HANDLER_H
#define CSV_HANDLER_H

#include "algorithms/algorithm_base.h"
#include "validator.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <random>
#include <set>
#include <sstream>
#include <string>
#include <sys/stat.h>
#include <unordered_set>
#include <utility>
#include <vector>

/*class CSVHandler
 * @brief A utility class for handling CSV file operations, including reading,
 * writing, and validation.
 */

class CSVHandler {
public:
  /**
   * @brief Reads the entire content of a file and returns it as a string.
   * Newlines are normalized.
   *
   * @param filename The name of the CSV file to read.
   * @return std::string The content of the CSV file. Returns an empty string if
   * an error occurs.
   */
  static std::string readFile(const std::string &filename);

  /**
   * @brief Reads a CSV file and parses its contents into a vector of rows,
   *        where each row is represented as a vector of strings (columns).
   *
   * @param filename The path to the CSV file.
   * @return A vector of rows, where each row is a vector of strings
   * representing the columns.
   *
   * @note This function assumes that the CSV file uses commas (`,`) as the
   * delimiter. It does not handle quoted values or escape characters.
   */
  static std::vector<std::vector<std::string>>
  readCSVAsVector(const std::string &filename);

  /**
   * @brief Converts the string representation of a CSV file to a 2D vector.
   *
   * @param str String representation of 2D vector
   * @return std::vector<std::vector<std::string>>
   */
  static std::vector<std::vector<std::string>>
  stringToVector(const std::string &str);

  /**
   * @brief Writes a string content to a specified file. Newlines are
   * normalized.
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

  /**
   * @brief Generates a CSV-formatted string with random integers. It works by
   * generating a random compressed CSV string and then unmerges it. This
   * approach ensures that the generated file contains rows that can actually be
   * compressed.
   *
   * @param rows The minimum number of rows in the final output.
   * @param cols The number of columns in each row.
   * @param maxLoad Maximum number of values in a merged cell. The minimum value
   * is 1.
   * @return A string containing the uncompressed CSV data.
   */
  static std::string generate(const int minRows, const int cols,
                              const int maxLoad);

  static std::string joinArrayWithPipe(const std::vector<int> &arr);
};

#endif // CSV_HANDLER_H
