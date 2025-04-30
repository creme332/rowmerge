#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <deque>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <utility> // for std::pair
#include <vector>

/**
 * @class Validator
 * @brief Contains functions for validating the output of a heuristic algorithm.
 * It only validates the output of Task 1 where the original merging rules are
 * applied. It does not work for the other tasks.
 *
 */
class Validator {
public:
  /**
   * @brief Checks whether `output` is a valid result after `input` has been
   * compressed. It works by unmerging each row of `output` and comparing it
   * with `input`.
   *
   * @param input Initial valid CSV file
   * @param output Final CSV file after compression
   * @return std::pair<bool, std::string>
   */
  static std::pair<bool, std::string> validateOutput(const std::string &input,
                                                     const std::string &output);

  /**
   * @brief Unmerges a list of rows (e.g. after compression algorithm was
   * applied) to give back original rows.
   *
   * @param rows List of rows in CSV format
   * @return std::vector<std::vector<std::string>> A 2D vector of rows that can
   * be merged to give `rows`.
   */
  static std::vector<std::vector<std::string>> unmergeRows(std::string rows);

  /**
   * @brief Unmerges a row and returns the initial list of rows.
   * For example `unmerge('1|2|3,2')` returns `['12', '22', '32']`. This
   * function is a wrapper for `unmerge(vector<string>, int, deque<string>)
   *
   * @param row A comma-separated row of values with possibly merged values
   * @return std::deque<std::string> List of rows that can be merged back to
   * `row`.
   */
  static std::deque<std::string> unmergeRow(std::string row);

private:
  /**
   * @brief Recursive function that unwraps a merged row and saves the result to
   * an array.
   *
   * @param columns Array where each element represents a column of a merged row
   * @param i Index of last element in columns
   * @param acc Accumulator for storing unmerged version of rows
   */
  static void unmergeRow(std::vector<std::string> columns, int i,
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
