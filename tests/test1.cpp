#include "../src/validator.h"
#include "doctest.h"
#include <deque>
#include <set>
#include <string>

/**
 * @brief Checks if two deques of strings are equal, ignoring the order of
 * elements.
 *
 * This function compares two deques of strings and determines if they contain
 * the same strings, disregarding the order. The deques must have the same
 * number of occurrences of each string, though the order of the elements in the
 * deques doesn't matter.
 *
 * It does this by converting both deques into `std::multiset` containers, which
 * automatically handle duplicates and store elements in sorted order. Once
 * converted, the multisets are compared for equality.
 *
 * @param expected The expected deque of strings.
 * @param result The result deque of strings.
 * @return True if the deques contain the same strings with the same frequency,
 * false otherwise.
 *
 * @note This function does not account for the order of elements, only their
 * presence and frequency. The elements must match exactly (same strings with
 * the same frequency).
 */
bool check_deque(const std::deque<std::string> &expected,
                 const std::deque<std::string> &result) {
  // Convert expected and result deques into multisets to disregard order and
  // handle duplicates
  std::multiset<std::string> set1(expected.begin(), expected.end());
  std::multiset<std::string> set2(result.begin(), result.end());

  // Compare the two multisets
  if (set1 != set2) {
    // If they don't match, print out what failed
    std::ostringstream failure_msg;
    failure_msg << "Failure: The deques do not match.\n";
    failure_msg << "Expected:\n";
    for (const auto &str : expected) {
      failure_msg << str << "\n";
    }
    failure_msg << "\nResult: ";
    for (const auto &str : result) {
      failure_msg << str << " ";
    }
    FAIL(failure_msg.str());
    return false;
  }
  return true;
}

TEST_CASE("Testing unmerge()") {
  using namespace std;

  SUBCASE("Basic Comma-Separated Values") {
    deque<string> result = Validator::unmerge("a,b,c");
    deque<string> expected = {"a,b,c"};
    CHECK(check_deque(result, expected));
  }

  SUBCASE("Empty string") {
    deque<string> result = Validator::unmerge("");
    CHECK(result.size() == 0);
  }

  SUBCASE("Single column") {
    deque<string> result = Validator::unmerge("hello");
    deque<string> expected = {"hello"};
    CHECK(check_deque(result, expected));
  }

  SUBCASE("Single column with pipe") {
    deque<string> result = Validator::unmerge("1|2|3");
    deque<string> expected = {"1", "2", "3"};

    CHECK(check_deque(result, expected));
  }

  SUBCASE("Normal case") {
    deque<string> result = Validator::unmerge("2,1|2|3,2,2,2");
    deque<string> expected = {"2,2,2,2,2", "2,1,2,2,2", "2,3,2,2,2"};
    CHECK(check_deque(expected, result));
  }
}
