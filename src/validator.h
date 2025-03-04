#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <deque>
#include <iostream>
#include <sstream>
#include <string>
#include <utility> // for std::pair
#include <vector>

/**
 * @class Validator
 * @brief Contains functions for validating the output of a heuristic algorithm.
 *
 */
class Validator {
public:
  std::pair<bool, std::string> validate(const std::string &str1,
                                        const std::string &str2);

  /**
   * @brief Unmerges a row and returns the initial list of rows.
   * For example `unmerge('1|2|3,2')` returns `['12', '22', '32']`
   *
   * @param row A comma-separated row of values with possibly merged values
   * @return std::deque<std::string> List of rows that can be merged back to
   * `row`.
   */
  static std::deque<std::string> unmerge(std::string row);

private:
  /**
   * @brief Recursive function that unwraps a merged row and saves the result to
   * an array.
   *
   * @param columns Array where each element represents a column of a merged row
   * @param i Index of last element in columns
   * @param acc Accumulator for storing unmerged version of rows
   */
  static void unmerge(std::vector<std::string> columns, int i,
                      std::deque<std::string> &acc);

  /**
   * @brief Splits a given string into a vector of substrings based on a
   * specified delimiter.
   *
   * This function takes an input string and splits it into multiple substrings
   * wherever the specified delimiter character appears. The resulting
   * substrings are stored in a `std::vector<std::string>` and returned.
   *
   * Reference: https://stackoverflow.com/a/46931770/17627866
   * 
   * @param s The input string to be split.
   * @param delim The character used as the delimiter to split the string.
   * @return A vector containing the substrings after splitting the input
   * string.
   **/
  static std::vector<std::string> split(const std::string &s, char delim);
};

#endif // VALIDATOR_H
