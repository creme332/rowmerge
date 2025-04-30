#include "multithread_algo.h"

std::string MultithreadedAlgorithm::solve(const std::string &input) {
  std::vector<std::vector<std::string>> inputAsVector =
      CSVHandler::stringToVector(input);
  return solve(inputAsVector);
}

std::string
MultithreadedAlgorithm::solve(std::vector<std::vector<std::string>> &input) {
  allRows_ = input;
  partitionRows();
  processPartitions();
  mergeThreadResults();

  return AlgorithmBase::vectorToCSV(compressedRows_);
}

void MultithreadedAlgorithm::partitionRows() {
  partitions_.resize(numThreads_);

  std::hash<std::string> rowHasher;

  for (const auto &row : allRows_) {
    // Convert row vector to a single string key for hashing
    std::string rowKey;
    for (const auto &cell : row) {
      rowKey += cell + "_"; // Delimiter to avoid collisions
    }

    size_t hashValue = rowHasher(rowKey);
    int partitionIndex = hashValue % numThreads_;

    partitions_[partitionIndex].push_back(row);
  }
}

void MultithreadedAlgorithm::processPartitions() {
  threadResults_.resize(numThreads_);
  std::vector<std::thread> threads;

  for (size_t i = 0; i < numThreads_; ++i) {
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
