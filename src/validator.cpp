#include "validator.h"

std::pair<bool, std::string> Validator::validate(const std::string &str1,
                                                 const std::string &str2) {
  if (str1.empty() || str2.empty()) {
    return {false, "One or both strings are empty."};
  }
  if (str1.length() != str2.length()) {
    return {false, "Strings are of different lengths."};
  }
  if (str1 != str2) {
    return {false, "Strings do not match."};
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

  // check if "|" symbol is not present in columns[i]
  if (columns[i].find('|') == std::string::npos) {
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

  // "|" symbol is present in columns
  // get each possible value for current column
  std::vector groups = split(columns[i], '|');

  // initialize acc if empty
  if (acc.size() == 0) {
    // push all elements of groups into acc
    for (auto g : groups) {
      acc.push_back(g);
    }
    unmerge(columns, i - 1, acc);
    return;
  }

  // create all possible combinations by combining each element of groups
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
