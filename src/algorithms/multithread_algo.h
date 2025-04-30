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
  void partitionRowsUsingHashing();

  /**
   * @brief Calculate the Hamming distance between two rows.
   *
   * The Hamming distance measures how many positions two rows of strings
   * differ. This method compares two rows element by element and returns the
   * number of differing elements.
   *
   * @param row1 The first row, represented as a vector of strings.
   * @param row2 The second row, represented as a vector of strings.
   *
   * @return The Hamming distance, which is the count of differing positions
   * between the two rows.
   */
  int hammingDistance(const std::vector<std::string> &row1,
                      const std::vector<std::string> &row2);

  /**
   * @brief Partition rows based on their Hamming distance.
   *
   * This method partitions the dataset into groups where each group contains
   * rows that are similar based on a defined Hamming distance threshold. The
   * rows in each group should differ minimally (according to the Hamming
   * distance). The partitioning is done using a threshold to decide the
   * grouping.
   */
  void partitionRowsUsingHammingDistance();

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
