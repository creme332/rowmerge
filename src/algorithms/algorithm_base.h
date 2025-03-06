#ifndef ALGORITHM_BASE_H
#define ALGORITHM_BASE_H

#include <string>
#include <vector>

class AlgorithmBase {
public:
  virtual ~AlgorithmBase() = default;
  virtual std::string solve(const std::string &input) = 0;
};

#endif
