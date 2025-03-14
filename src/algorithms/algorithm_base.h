#ifndef ALGORITHM_BASE_H
#define ALGORITHM_BASE_H

#include <sstream>
#include <string>
#include <vector>
class AlgorithmBase {
public:
  virtual ~AlgorithmBase() = default;

  virtual std::string solve(const std::string &input) = 0;

  virtual std::string solve(std::vector<std::vector<std::string>> &input) = 0;

  /**
   * @brief Joins all elements of a vector with a comma
   *
   * @param vec Vector of strings
   * @return std::string CSV format of vector
   */
  static std::string joinWithComma(const std::vector<std::string> &vec) {
    std::ostringstream oss;
    for (size_t i = 0; i < vec.size(); ++i) {
      if (i != 0) {
        oss << ",";
      }
      oss << vec[i];
    }
    return oss.str();
  }
};

#endif
