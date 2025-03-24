#ifndef NEW_ALGO_H // TODO: change the name of the guards
#define NEW_ALGO_H

#include "algorithm_base.h"
#include <algorithm>
#include <optional>
#include <stdexcept>

/**
 * @brief A template for creating algorithms.
 * TODO: Change the class name.
 *
 */
class NewAlgorithm : public AlgorithmBase {
public:
  std::string solve(const std::string &input) override;

  std::string solve(std::vector<std::vector<std::string>> &input) override;

  static bool canMerge(const std::vector<std::string>& row1, 
    const std::vector<std::string>& row2, 
    int& diffIndex);

/**
* @brief Merges two rows at the differing column.
* @param row1 Row to be updated
* @param row2 Row to be merged
* @param mergeColumn The column where merging happens
*/
static void mergeRows(std::vector<std::string>& row1, 
     const std::vector<std::string>& row2, 
     int mergeColumn);

}; 

#endif