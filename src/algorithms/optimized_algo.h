#ifndef OPTIMIZED_ALGO_H
#define OPTIMIZED_ALGO_H

#include <vector>
#include <string>
#include <unordered_map>
 
class OptimizedAlgorithm {
public:
    std::string solve(std::vector<std::vector<std::string>>& input);

private:
    bool canMerge(const std::vector<std::string>& row1, 
                  const std::vector<std::string>& row2, 
                  int& diffIndex);

    void mergeRows(std::vector<std::string>& row1, 
                   const std::vector<std::string>& row2, 
                   int mergeColumn);
};

#endif // OPTIMIZED_ALGO_H
