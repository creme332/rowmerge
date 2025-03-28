#ifndef TRIVIAL_ALGO_H
#define TRIVIAL_ALGO_H

#include "algorithm_base.h"
#include <algorithm>
#include <optional>
#include <stdexcept>

class TrivialAlgorithm : public AlgorithmBase {
public:
  std::string solve(const std::string &input) override;

  std::string solve(std::vector<std::vector<std::string>> &input) override;

  /**
   * @brief Performs clustering based on a number of parameters
   *
   * @param input Vector representation of CSV file
   * @param startColumn Index of column where processing starts
   * @param columnCount Number of columns to be processed
   * @param forwardPass If set to true, columns will be processed from left to
   * right. Otherwise, columns will be processed from right to left.
   * @return std::string CSV format of compressed output
   */
  static std::string
  clusterByColumns(std::vector<std::vector<std::string>> input,
                   const int startColumn, int columnCount, bool forwardPass);
};

#endif
