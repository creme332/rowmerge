#ifndef SAMPLE_ALGO_H // TODO: change the name of the guards
#define SAMPLE_ALGO_H

#include "algorithm_base.h"
#include <algorithm>
#include <optional>
#include <stdexcept>

/**
 * @brief A template for creating algorithms.
 * TODO: Change the class name.
 *
 */
class SampleAlgorithm : public AlgorithmBase {
public:
  std::string solve(const std::string &input) override;

  std::string solve(std::vector<std::vector<std::string>> &input) override;
}; 

#endif
