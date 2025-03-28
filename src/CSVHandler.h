#ifndef CSV_HANDLER_H
#define CSV_HANDLER_H

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
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
   * @brief Reads the entire content of a CSV file and returns it as a string.
   *
   * @param filename The name of the CSV file to read.
   * @return std::string The content of the CSV file. Returns an empty string if
   * an error occurs.
   */
  static std::string readCSVAsString(const std::string &filename);

  /**
   * @brief Reads the entire content of a CSV file and returns it as a vector.
   *
   * @param filename The name of the CSV file to read.
   * @return std::string The content of the CSV file. Returns an empty string if
   * an error occurs.
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

  /**
   * @brief Generates a CSV-formatted string with random integers.
   *
   * This function creates a CSV-formatted string with the given number of rows
   * and columns. Each row is unique, and all rows contain the same number of
   * columns. Each cell contains a randomly generated small integer.
   *
   * @param rows The number of rows in the CSV.
   * @param cols The number of columns in each row.
   * @return A string containing the generated CSV data.
   */
  static std::string generate(const int rows, const int cols);
};

#endif // CSV_HANDLER_H
