#include "trivial_algo.h"

std::string TrivialAlgorithm::solve(const std::string &input) {
  throw std::runtime_error("Implementation missing");
  return "";
}

std::string
TrivialAlgorithm::solve(std::vector<std::vector<std::string>> &input) {
  throw std::runtime_error("Implementation missing");
  return "";
}

std::string TrivialAlgorithm::insertSorted(const std::string sortedStr,
                                           const std::string newElement) {
  if (sortedStr.empty())
    return newElement; // If the sorted string is empty, return the new element.

  std::vector<std::string> elements;
  std::stringstream ss(sortedStr);
  std::string item;

  // Split the input string into a vector
  while (std::getline(ss, item, '|')) {
    elements.push_back(item);
  }

  // Use lower_bound to find the correct insertion position
  auto it = std::lower_bound(elements.begin(), elements.end(), newElement);

  // Insert the new element while maintaining sorted order
  elements.insert(it, newElement);

  // Construct the sorted string
  std::ostringstream result;
  for (size_t i = 0; i < elements.size(); ++i) {
    if (i > 0)
      result << "|";
    result << elements[i];
  }

  return result.str();
}

std::unordered_set<int> findDifferences(const std::vector<std::string> &vec1,
                                        const std::vector<std::string> &vec2) {
  std::unordered_set<int> diffIndices;

  // Ensure both vectors have the same size
  if (vec1.size() != vec2.size()) {
    throw std::out_of_range("Error: Vectors must be of the same length.\n");
  }

  // Compare elements and store indices where they differ
  for (size_t i = 0; i < vec1.size(); ++i) {
    if (vec1[i] != vec2[i]) {
      diffIndices.insert(i);
    }
  }

  return diffIndices;
}

std::string
TrivialAlgorithm::clusterByColumns(std::vector<std::vector<std::string>> input,
                                   const int startColumn, int columnCount,
                                   const bool forwardPass) {
  // determine the number of columns in each row
  const int totalColumns = input[0].size();

  // validate startColumn
  if (startColumn < 0 || startColumn >= totalColumns) {
    throw std::out_of_range(
        "Error: startColumn is out of valid range. Valid range = 0 - " +
        std::to_string(totalColumns - 1));
  }

  // validate columnCount
  if (columnCount < 1) {
    throw std::invalid_argument("Error: columnCount must be positive.");
  }

  // calculate index of last column if forward pass is used. Ensure value is not
  // out of bounds.
  const int lastColumnForwardPass =
      std::min(startColumn + columnCount - 1, totalColumns - 1);

  // calculate index of last column if backward pass is used. Ensure value is
  // not out of bounds.
  const int lastColumnBackwardPass = std::max(startColumn - columnCount + 1, 0);

  // initialize index of column where clustering will start.
  const int lastColumn =
      (forwardPass ? lastColumnForwardPass : lastColumnBackwardPass);

  // for each column to be clustered
  for (int currentMergeColumn = startColumn;
       (forwardPass ? currentMergeColumn <= lastColumn
                    : currentMergeColumn >= lastColumn);
       currentMergeColumn += forwardPass ? 1 : -1) {

    // process each row in a top-down approach
    for (int row = 0; row < input.size(); row++) {

      // skip empty/deleted rows
      std::vector<std::string> &currentRow = input[row];
      if (currentRow.empty())
        continue;

      // look for a row that differs from current row only at currentMergeColumn
      for (int nrow = row + 1; nrow < input.size(); nrow++) {
        const std::vector<std::string> otherRow = input[nrow];

        // skip rows which have already been processed/deleted
        if (input[nrow].empty())
          continue;

        // look for a row which differs from row by only currentMergeColumn
        if (currentRow[currentMergeColumn] == otherRow[currentMergeColumn])
          continue;

        bool goodRow = true;

        for (int col = 0; col < currentRow.size(); col++) {
          if (col != currentMergeColumn && currentRow[col] != otherRow[col]) {
            goodRow = false;
            break;
          }
        }

        if (goodRow) {
          // merge row and nrow at column currentMergeColumn
          currentRow[currentMergeColumn] = insertSorted(
              currentRow[currentMergeColumn], otherRow[currentMergeColumn]);
          input[nrow] = {};
        }
      }
    }
    // decrement number of columns remaining for processing
    columnCount--;
    if (columnCount <= 0)
      break;
  }

  // join rows with newlines
  std::string result = "";
  for (int row = 0; row < input.size(); row++) {
    if (!input[row].empty())
      result += AlgorithmBase::joinWithComma(input[row]) + "\n";
  }

  return result;
}