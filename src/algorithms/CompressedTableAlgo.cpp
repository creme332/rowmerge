#include "CompressedTableAlgo.h"
#include "CSVHandler.h"

/**
 * @brief Determines if two rows can be merged based on a single differing value.
 *
 * @param row1 The first row.
 * @param row2 The second row.
 * @param diffIndex The index of the differing value (if mergeable).
 * @return true if mergeable, false otherwise.
 */
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

/**
 * @brief Compresses a table by merging rows with a single differing value.
 *
 * @param input The input table as a 2D vector.
 * @return The compressed table as a 2D vector.
 */
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

/**
 * @brief Solves the compression task using the compressTable function.
 *
 * @param input The input CSV data as a string.
 * @return The compressed table as a CSV string.
 */
std::string CompressedTableAlgorithm::solve(const std::string &input) {
    CSVHandler csvHandler;
    std::vector<std::vector<std::string>> table = csvHandler.readCSVAsVector(input);
    std::vector<std::vector<std::string>> compressedTable = compressTable(table);
    
    std::stringstream output;
    for (const auto &row : compressedTable) {
        for (size_t i = 0; i < row.size(); ++i) {
            output << row[i];
            if (i < row.size() - 1) output << ",";
        }
        output << "\n";
    }
    return output.str();
}
