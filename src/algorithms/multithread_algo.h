#ifndef MULTITHREADED_ALGO_H
#define MULTITHREADED_ALGO_H

#include "../CSVHandler.h"
#include "algorithm_base.h"
#include "trivial_algo.h"
#include <algorithm>
#include <functional> // for std::hash
#include <math.h>
#include <mutex>
#include <optional>
#include <stdexcept>
#include <thread>

/**
 * @brief A multi-threaded algorithm for clustering rows.
 *
 */
class MultithreadedAlgorithm : public AlgorithmBase {
public:
  std::string solve(const std::string &input) override;

  std::string solve(std::vector<std::vector<std::string>> &input) override;

private:
  const unsigned int numThreads_ =
      std::max(1u, std::thread::hardware_concurrency() / 2);

  std::vector<std::vector<std::string>> allRows_; // Input matrix
  std::vector<std::vector<std::string>>
      compressedRows_; // Final flat output container

  std::vector<std::vector<std::vector<std::string>>>
      partitions_; // [thread][row][column]
  std::vector<std::vector<std::vector<std::string>>> threadResults_;

  std::mutex resultMutex_; // For thread-safe writes to threadResults_

  /**
   * @brief Partition rows across threads (hash-based)
   *
   * This method distributes input rows into partitions based on a hash of the
   * row content. It ensures that similar rows are likely
   * assigned to the same thread, increasing the chance for compression via
   * merging.
   */
  void partitionRows();

  /**
   * @brief Launch threads to process each partition
   *
   * Each thread runs independently on a separate partition of the dataset,
   * applying the row merging/compression logic in parallel.
   */
  void processPartitions();

  /**
   * @brief Merge compressed results from all threads
   *
   * This method gathers and combines the outputs produced by each thread
   * into a final unified dataset for output.
   */
  void mergeThreadResults();
};

#endif
