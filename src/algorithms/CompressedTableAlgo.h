#ifndef COMPRESSED_TABLE_ALGO_H
#define COMPRESSED_TABLE_ALGO_H

#include "algorithm_base.h"
#include <vector>
#include <string>
#include <set>

/**
 * @brief Algorithm to compress a table while ensuring reversibility.
 */
class CompressedTableAlgorithm : public AlgorithmBase {
public:
    std::string solve(const std::string &input) override;
    
private:
    bool canMerge(const std::vector<std::string> &row1, const std::vector<std::string> &row2, int &diffIndex);
    std::vector<std::vector<std::string>> compressTable(std::vector<std::vector<std::string>> &input);
};

bool CompressedTableAlgorithm::canMerge(const std::vector<std::string> &row1, const std::vector<std::string> &row2, int &diffIndex) {
    int diffCount = 0;
    for (size_t i = 0; i < row1.size(); ++i) {
        if (row1[i] != row2[i]) {
            diffIndex = i;
            if (++diffCount > 1) return false;
        }
    }
    return diffCount == 1;
}

std::vector<std::vector<std::string>> CompressedTableAlgorithm::compressTable(std::vector<std::vector<std::string>> &input) {
    std::vector<std::vector<std::string>> compressed;
    std::set<int> merged;

    for (size_t i = 0; i < input.size(); ++i) {
        if (merged.count(i)) continue;
        std::vector<std::string> mergedRow = input[i];
        
        for (size_t j = i + 1; j < input.size(); ++j) {
            if (merged.count(j)) continue;
            int diffIndex;
            if (canMerge(mergedRow, input[j], diffIndex)) {
                merged.insert(j);
                mergedRow[diffIndex] += "|" + input[j][diffIndex];
            }
        }
        compressed.push_back(mergedRow);
    }
    return compressed;
}

std::string CompressedTableAlgorithm::solve(const std::string &input) {
    // Implement conversion from string input to table, apply compression, then convert back to string
    return "Compressed table output as string";
}

#endif
