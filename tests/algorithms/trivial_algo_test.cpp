#include "../../src/algorithms/trivial_algo.h"
#include "../doctest.h"

TEST_SUITE("TrivialAlgorithm") {
  TEST_CASE("clusterWithRowDuplication - basic duplication case") {
    TrivialAlgorithm algo;

    std::vector<std::vector<std::string>> input = {
        {"A", "B", "C"}, {"A", "B", "D"}, {"A", "E", "C"}};

    std::string result = algo.clusterWithRowDuplication(input);

    CHECK(result == "A,B|E,C\nA,B,D|C^\n");
  }

  TEST_CASE("clusterWithRowDuplication - no merging possible") {
    TrivialAlgorithm algo;
    std::vector<std::vector<std::string>> input = {
        {"1", "2", "3"}, {"4", "5", "6"}, {"7", "8", "9"}};
    std::string result = algo.clusterWithRowDuplication(input);

    CHECK("1,2,3\n4,5,6\n7,8,9\n");
  }

  TEST_CASE("clusterByColumns - left to right clustering") {
    TrivialAlgorithm algo;

    std::vector<std::vector<std::string>> input = {
        {"1", "2", "3"}, {"2", "2", "3"}, {"3", "1", "1"}, {"3", "2", "1"}};

    std::string result = algo.clusterByColumns(input, 0, 2, true);

    CHECK(result == "1|2,2,3\n3,1|2,1\n");
  }

  TEST_CASE("clusterByColumns - right to left clustering") {
    TrivialAlgorithm algo;

    std::vector<std::vector<std::string>> input = {
        {"1", "2", "5"}, {"1", "2", "6"}, {"1", "2", "8"}};

    std::string result = algo.clusterByColumns(input, 2, 1, false);

    CHECK(result == "1,2,5|6|8\n");
  }

  TEST_CASE("clusterWithTolerance - tolerance = 1") {
    TrivialAlgorithm algo;

    std::vector<std::vector<std::string>> input = {
        {"1", "2", "3"},
        {"3", "5", "3"},
    };

    std::string result = algo.clusterWithTolerance(input, 1);

    CHECK(result == "1,2,3\n3,5,3\n");
  }

  TEST_CASE("clusterWithTolerance - tolerance = 2") {
    TrivialAlgorithm algo;

    std::vector<std::vector<std::string>> input = {
        {"1", "2", "3"},
        {"3", "5", "3"},
    };

    std::string result = algo.clusterWithTolerance(input, 2);

    CHECK(result == "1|3,2|5,3\n");
  }

  TEST_CASE("clusterWithTolerance - tolerance = 3") {
    TrivialAlgorithm algo;

    std::vector<std::vector<std::string>> input = {
        {"1", "2", "3"},
        {"4", "5", "6"},
    };

    std::string result = algo.clusterWithTolerance(input, 3);

    CHECK(result == "1|4,2|5,3|6\n");
  }

  TEST_CASE("solve(string) - trivial input") {
    TrivialAlgorithm algo;
    std::string input = "1,2,3\n2,2,3\n";

    std::string result = algo.solve(input);

    CHECK("1|2,2,3\n");
  }

  TEST_CASE("solve(string) - no merging possible") {
    TrivialAlgorithm algo;
    std::string input = "1,2,3\n4,5,6\n7,8,9\n";

    std::string result = algo.solve(input);

    CHECK("1,2,3\n4,5,6\n7,8,9\n");
  }

  TEST_CASE("solve(vector<vector<string>>) - minimal case") {
    TrivialAlgorithm algo;
    std::vector<std::vector<std::string>> input = {{"1", "2"}, {"5", "3"}};

    std::string result = algo.solve(input);
    CHECK(result == "1,2\n5,3\n");
  }
}
