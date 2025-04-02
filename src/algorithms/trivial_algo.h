#ifndef TRIVIAL_ALGO_H
#define TRIVIAL_ALGO_H

#include "algorithm_base.h"
#include <algorithm>
#include <optional>
#include <stdexcept>
#include <unordered_set>

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
                   const int startColumn, int columnCount,
                   const bool forwardPass);

  static std::string
  clusterWithTolerance(std::vector<std::vector<std::string>> input,
                       int tolerance);

private:
  /**
   * @brief Finds the indices where two vectors of strings differ.
   *
   * This function compares two vectors of strings element by element and
   * returns a vector of indices where the corresponding elements are different.
   *
   * @param vec1 The first vector of strings.
   * @param vec2 The second vector of strings.
   * @return std::unordered_set<int> A set containing the indices where the two
   * input vectors differ. If the vectors have different sizes, an error message
   * is displayed, and an empty vector is returned.
   */
  static std::unordered_set<int>
  findDifferences(const std::vector<std::string> &vec1,
                  const std::vector<std::string> &vec2);

  /**
   * @brief Inserts a new element into a sorted string while maintaining sorted
   * order.
   *
   * This function takes a string of sorted elements separated by the '|'
   * delimiter and efficiently inserts a new element while preserving the sorted
   * order.
   *
   * @param sortedStr A string containing sorted elements separated by '|'.
   * @param newElement The element to be inserted while keeping the string
   * sorted.
   * @return A new sorted string with the inserted element.
   *
   * @note The function uses binary search (`std::lower_bound`) for efficient
   * insertion.
   *
   */
  static std::string insertSorted(const std::string sortedStr,
                                  const std::string newElement);
};

#endif
