#include "validator.h"

std::pair<bool, std::string>
Validator::validate_output(const std::string &input,
                           const std::string &output) {
  if (input.empty() && output.empty()) {
    return {true, "Validation successful."};
  }

  if (!input.empty() && output.empty()) {
    return {false, "Output should not be empty."};
  }

  if (input.empty() && !output.empty()) {
    return {false, "Output should be empty."};
  }

  // create a vector of input rows
  std::vector in_rows = split(input, '\n');

  // create a vector of output rows
  std::vector out_rows = split(output, '\n');

  // Create a map where the key is a row in input and
  // the value represents whether or not the row is missing from output
  std::map<std::string, int> row_counter;
  for (std::string row : in_rows) {
    // ignore empty rows and assume all remaining rows are missing from output
    if (row.size() > 0)
      row_counter.insert({row, 1});
  }

  for (std::string row : out_rows) {
    // unmerge each row in output
    std::deque<std::string> unmerged_rows = unmerge(row);
    for (std::string urow : unmerged_rows) {

      // Finding element with key
      auto it = row_counter.find(urow);

      if (it == row_counter.end()) {
        // output contains extra row
        return {false, "Output contains a row not found in input: " + urow +
                           "\n"
                           "Original row from output: " +
                           row};
      } else {
        // row is present in input

        // check if output produced duplicate rows
        if (it->second == 0) {
          return {false, "Duplicate row in output: "
                         "Unmerging " +
                             row + " produces " + urow +
                             " which occurs more than once"};
        } else {
          row_counter[urow] = 0;
        }
      }
    }
  }

  // check if all input rows have count 0
  for (auto it = row_counter.begin(); it != row_counter.end(); ++it)
    if (it->second == 1) {
      return {false, "Missing row in output: " + it->first};
    }

  return {true, "Validation successful."};
}

std::deque<std::string> Validator::unmerge(std::string row) {
  // put each column in an array
  std::vector columns = split(row, ',');

  // create an accumulator to store result
  std::deque<std::string> acc;

  unmerge(columns, columns.size() - 1, acc);

  return acc;
}

void Validator::unmerge(std::vector<std::string> columns, int i,
                        std::deque<std::string> &acc) {
  if (i < 0 || columns.size() == 0)
    return;

  // Case 1: "|" symbol is not present in current column

  if (columns[i].find('|') == std::string::npos) {
    // initialize acc if empty
    if (acc.size() == 0) {
      acc.push_back(columns[i]);
    } else {
      // prepend columns[i] to each element in accumulator
      for (int j = 0; j < acc.size(); j++) {
        acc[j] = columns[i] + "," + acc[j];
      }
    }
    unmerge(columns, i - 1, acc);
    return;
  }

  // Case 2: "|" symbol is present in current column

  // split current column using pipe symbol as separator
  std::vector groups = split(columns[i], '|');

  // Case 2.1: Accumulator is empty

  // initialize empty acc with all elements in current column
  if (acc.size() == 0) {
    // push all elements of groups into acc
    for (auto g : groups) {
      acc.push_back(g);
    }
    // unmerge remaining columns
    unmerge(columns, i - 1, acc);
    return;
  }

  // Case 2.2: Accumulator is non-empty
  // Create all possible combinations by combining each element of groups
  // with each element of acc
  int count = acc.size();
  while (count--) {
    // pop first element of acc
    std::string front = acc.front();
    acc.pop_front();

    // add new combination to acc
    for (std::string g : groups) {
      acc.push_back(g + "," + front);
    }
  }

  unmerge(columns, i - 1, acc);
}

std::vector<std::string> Validator::split(const std::string &s, char delim) {
  std::vector<std::string> result;
  std::stringstream ss(s);
  std::string item;

  while (getline(ss, item, delim)) {
    result.push_back(item);
  }

  return result;
}
