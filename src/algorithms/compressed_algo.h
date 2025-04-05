#ifndef COMPRESSED_TABLE_ALGO_H
#define COMPRESSED_TABLE_ALGO_H

#include "../CSVHandler.h"
#include "algorithm_base.h"
#include <set>
#include <string>
#include <vector>

/**
 * @brief Algorithm to compress a table while ensuring reversibility.
 */
class CompressedTableAlgorithm : public AlgorithmBase {
public:
  std::string solve(const std::string &input) override;

  std::string solve(std::vector<std::vector<std::string>> &input) override;

private:
  bool canMerge(const std::vector<std::string> &row1,
                const std::vector<std::string> &row2, int &diffIndex);
  std::vector<std::vector<std::string>>
  compressTable(std::vector<std::vector<std::string>> &input);
};

#endif
