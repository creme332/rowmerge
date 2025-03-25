#include "new_algo.h" // TODO: Change header file

// TODO: Replace SampleAlgorithm with the name of your class

std::string NewAlgorithm::solve(const std::string &input) {
  throw std::runtime_error("Implementation missing");
  return "";
}

std::string
NewAlgorithm::solve(std::vector<std::vector<std::string>> &input) {

    std::vector<bool> merged(input.size(), false); // Track merged rows

  for (int i = 0; i < input.size(); i++) {
    if (merged[i]) continue; // Skip already merged rows

    for (int j = i + 1; j < input.size(); j++) {
      if (merged[j]) continue; // Skip already merged rows

      int mergeColumn = -1;
      if (canMerge(input[i], input[j], mergeColumn)) {
        mergeRows(input[i], input[j], mergeColumn);
        merged[j] = true; // Mark row as merged (to be deleted)
      }
    }
  }

  // Remove merged rows from the dataset
  std::vector<std::vector<std::string>> result;
  for (int i = 0; i < input.size(); i++) {
    if (!merged[i]) result.push_back(input[i]);
  }

  // Convert result to string format
  std::string output;
  for (const auto &row : result) {
    for (size_t col = 0; col < row.size(); col++) {
      output += row[col];
      if (col < row.size() - 1) output += ", ";
    }
    output += "\n";
  }
  return output;
}

bool NewAlgorithm::canMerge(const std::vector<std::string>& row1, 
                               const std::vector<std::string>& row2, 
                               int& diffIndex) {
  int diffCount = 0;
  for (int i = 0; i < row1.size(); i++) {
    if (row1[i] != row2[i]) {
      diffCount++;
      diffIndex = i;
      if (diffCount > 1) return false; // More than one difference → Cannot merge
    }
  }
  return (diffCount == 1); // Must differ in exactly one column
}

void NewAlgorithm::mergeRows(std::vector<std::string>& row1, 
                                const std::vector<std::string>& row2, 
                                int mergeColumn) {
  row1[mergeColumn] += "|" + row2[mergeColumn]; // Merge the differing column
} 



    //   throw std::runtime_error("Implementation missing");
//   return "";
// } 