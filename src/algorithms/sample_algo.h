#ifndef SAMPLE_ALGO_H
#define SAMPLE_ALGO_H

#include "algorithm_base.h"

class SampleAlgorithm : public AlgorithmBase {
public:
  std::string solve(const std::string &input) override;
};

#endif
