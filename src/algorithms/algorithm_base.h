#ifndef ALGORITHM_BASE_H
#define ALGORITHM_BASE_H

#include <sstream>
#include <string>
#include <vector>

/**
 * @brief Base class for a CSV solver.
 *
 */
class AlgorithmBase {
public:
  virtual ~AlgorithmBase() = default;

  /**
   * @brief Compresses CSV using default merging rules. No row repetition or
   * variable tolerance allowed.
   *
   * @param input CSV file in string format
   * @return std::string
   */
  virtual std::string solve(const std::string &input) = 0;

  /**
   * @brief Compresses CSV using default merging rules. No row repetition or
   * variable tolerance allowed.
   *
   * @param input CSV file as a 2D vector
   * @return std::string
   */
  virtual std::string solve(std::vector<std::vector<std::string>> &input) = 0;

  /**
   * @brief Converts a 1D vector to comma separated format
   *
   * @param vec Vector of strings
   * @return std::string CSV format of vector
   */
  static std::string vectorToCSV(const std::vector<std::string> &vec) {
    std::ostringstream oss;
    for (size_t i = 0; i < vec.size(); ++i) {
      if (i != 0) {
        oss << ",";
      }
      oss << vec[i];
    }
    return oss.str();
  }

  /**
   * @brief Converts a 2D vector to string format. Empty rows are ignored.
   *
   * @param input 2D vector of string
   * @return std::string
   */
  static std::string
  vectorToCSV(const std::vector<std::vector<std::string>> &input) {
    std::string result = "";
    for (int row = 0; row < input.size(); row++) {
      if (!input[row].empty())
        result += vectorToCSV(input[row]) + "\n";
    }
    return result;
  }
};

#endif
