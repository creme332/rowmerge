#include "multithread_algo.h"

std::string MultithreadedAlgorithm::solve(const std::string &input) {
  std::vector<std::vector<std::string>> inputAsVector =
      CSVHandler::stringToVector(input);
  return solve(inputAsVector);
}

std::string
MultithreadedAlgorithm::solve(std::vector<std::vector<std::string>> &input) {
  if (input.size() <= 100) {
    TrivialAlgorithm algo;
    return algo.solve(input);
  }

  partitions_.clear();
  threadResults_.clear();
  compressedRows_.clear();
  allRows_ = input;

  partitionRowsUsingHammingDistance();
  processPartitions();
  mergeThreadResults();

  return AlgorithmBase::vectorToCSV(compressedRows_);
}

void MultithreadedAlgorithm::partitionRowsUsingHashing() {
  partitions_.resize(numThreads_);

  std::hash<std::string> rowHasher;

  for (const auto &row : allRows_) {
    // Convert row vector to a single string key for hashing
    std::string rowKey;
    for (const auto &cell : row) {
      rowKey += cell + "_";
    }

    size_t hashValue = rowHasher(rowKey);
    int partitionIndex = hashValue % numThreads_;

    partitions_[partitionIndex].push_back(row);
  }
}

int MultithreadedAlgorithm::hammingDistance(
    const std::vector<std::string> &row1,
    const std::vector<std::string> &row2) {
  int distance = 0;
  for (size_t i = 0; i < row1.size(); ++i) {
    if (row1[i] != row2[i]) {
      ++distance;
    }
  }
  return distance;
}

void MultithreadedAlgorithm::partitionRowsUsingHammingDistance() {
  partitions_.resize(numThreads_);

  // Vector to track whether a row has been assigned to a partition
  std::vector<bool> rowAssigned(allRows_.size(), false);

  // Iterate over all rows and group them based on Hamming distance
  for (size_t i = 0; i < allRows_.size(); ++i) {
    if (rowAssigned[i])
      continue; // Skip if this row is already assigned

    // Create a new partition for this row
    int partitionIndex =
        i % numThreads_; // Choose partition index (can be optimized later)

    partitions_[partitionIndex].push_back(allRows_[i]);
    rowAssigned[i] = true;

    // Try to find similar rows (with Hamming distance <= 1) and assign them to
    // the same partition
    for (size_t j = i + 1; j < allRows_.size(); ++j) {
      if (rowAssigned[j])
        continue;

      if (hammingDistance(allRows_[i], allRows_[j]) <= 1) {
        partitions_[partitionIndex].push_back(allRows_[j]);
        rowAssigned[j] = true;
      }
    }
  }
}

void MultithreadedAlgorithm::processPartitions() {
  threadResults_.resize(numThreads_);
  std::vector<std::thread> threads;

  for (size_t i = 0; i < numThreads_; ++i) {
    std::cout << "Partition " << i << " : " << partitions_[i].size()
              << std::endl;

    threads.emplace_back([this, i]() {
      std::vector<std::vector<std::string>> &partition = partitions_[i];

      TrivialAlgorithm algo;

      std::vector<std::vector<std::string>> localCompressed =
          CSVHandler::stringToVector(algo.solve(partition));

      // Lock before writing to shared threadResults_
      {
        std::lock_guard<std::mutex> lock(resultMutex_);
        threadResults_[i] = std::move(localCompressed);
      }
    });
  }

  for (auto &t : threads) {
    t.join();
  }
}

void MultithreadedAlgorithm::mergeThreadResults() {
  compressedRows_.clear();

  for (const auto &threadResult : threadResults_) {
    compressedRows_.insert(compressedRows_.end(), threadResult.begin(),
                           threadResult.end());
  }
}
