#include "sample_algo.h"

std::string SampleAlgorithm::solve(const std::string &input) {
  throw std::runtime_error("Implementation missing");
  return "";
}

std::string
SampleAlgorithm::solve(std::vector<std::vector<std::string>> &input) {
  throw std::runtime_error("Implementation missing");
  return "";
}

std::string
SampleAlgorithm::clusterByColumns(std::vector<std::vector<std::string>> input,
                                  int columnCount, bool forwardPass) {
  // initialize index of column where clustering will start. For forward pass
  // start at 0 and for backward pass start at last column index
  const int lastColumnIndex = input[0].size() - 1;
  const int firstColumnMergeIndex = (forwardPass ? 0 : lastColumnIndex);

  for (int currentMergeColumn = firstColumnMergeIndex;
       (forwardPass ? currentMergeColumn <= lastColumnIndex
                    : currentMergeColumn >= 0);
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