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

std::string
TrivialAlgorithm::clusterByColumns(std::vector<std::vector<std::string>> input,
                                   const int startColumn, int columnCount,
                                   bool forwardPass) {
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
      const std::string currentRowCol = currentRow[currentMergeColumn];

      // look for a row that differs from current row only at currentMergeColumn
      for (int nrow = row + 1; nrow < input.size(); nrow++) {
        const std::vector<std::string> otherRow = input[nrow];

        // skip rows which have already been processed/deleted
        if (input[nrow].empty())
          continue;

        // look for a row which differs from row by only currentMergeColumn
        if (currentRowCol == otherRow[currentMergeColumn])
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
          currentRow[currentMergeColumn] += "|" + otherRow[currentMergeColumn];
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