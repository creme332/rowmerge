#ifndef OPTIMIZED_ALGO_H
#define OPTIMIZED_ALGO_H

#include "algorithm_base.h"
#include <string>
#include <unordered_map>
#include <vector>

class OptimizedAlgorithm : public AlgorithmBase {
public:
  std::string solve(const std::string &input) override;
  std::string solve(std::vector<std::vector<std::string>> &input);

private:
  bool canMerge(const std::vector<std::string> &row1,
                const std::vector<std::string> &row2, int &diffIndex);

  void mergeRows(std::vector<std::string> &row1,
                 const std::vector<std::string> &row2, int mergeColumn);
};

#endif // OPTIMIZED_ALGO_H
