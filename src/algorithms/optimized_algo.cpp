#include "optimized_algo.h"
#include <iostream>
#include <utility> // for std::pair

std::string OptimizedAlgorithm::solve(std::vector<std::vector<std::string>>& input) {
    // Step 1: Preprocessing and grouping
    std::unordered_map<std::string, std::vector<int>> groups; // Key: omitted row, Value: indices of rows
    for (int i = 0; i < input.size(); i++) {
        for (int omitCol = 0; omitCol < input[i].size(); omitCol++) {
            std::string key;
            for (int col = 0; col < input[i].size(); col++) {
                if (col != omitCol) {
                    key += input[i][col] + ",";
                }
            }
            groups[key].push_back(i);
        }
    }

    // Step 2: Merge rows in groups
    std::vector<bool> merged(input.size(), false);
    for (const auto& group : groups) {
        const std::vector<int>& rowIndices = group.second;
        for (int i = 0; i < rowIndices.size(); i++) {
            if (merged[rowIndices[i]]) continue;
            for (int j = i + 1; j < rowIndices.size(); j++) {
                if (merged[rowIndices[j]]) continue;
                int diffIndex = -1;
                if (canMerge(input[rowIndices[i]], input[rowIndices[j]], diffIndex)) {
                    mergeRows(input[rowIndices[i]], input[rowIndices[j]], diffIndex);
                    merged[rowIndices[j]] = true;
                }
            }
        }
    }

    // Step 3: Collect unmerged rows
    std::vector<std::vector<std::string>> result;
    for (int i = 0; i < input.size(); i++) {
        if (!merged[i]) result.push_back(input[i]);
    }

    // Step 4: Convert result to string
    std::string output;
    for (const auto& row : result) {
        for (size_t col = 0; col < row.size(); col++) {
            output += row[col];
            if (col < row.size() - 1) output += ", ";
        }
        output += "\n";
    }
    return output;
}

bool OptimizedAlgorithm::canMerge(const std::vector<std::string>& row1, 
                                  const std::vector<std::string>& row2, 
                                  int& diffIndex) {
    int diffCount = 0;
    for (int i = 0; i < row1.size(); i++) {
        if (row1[i] != row2[i]) {
            diffCount++;
            diffIndex = i;
            if (diffCount > 1) return false;
        }
    }
    return (diffCount == 1);
}

void OptimizedAlgorithm::mergeRows(std::vector<std::string>& row1, 
                                   const std::vector<std::string>& row2, 
                                   int mergeColumn) {
    row1[mergeColumn] += "|" + row2[mergeColumn];
}
