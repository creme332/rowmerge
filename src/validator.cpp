#include "validator.h"

std::pair<bool, std::string> Validator::validate(const std::string &str1,
                                                 const std::string &str2) {
  if (str1.empty() || str2.empty()) {
    return {false, "One or both strings are empty."};
  }
  if (str1.length() != str2.length()) {
    return {false, "Strings are of different lengths."};
  }
  if (str1 != str2) {
    return {false, "Strings do not match."};
  }
  return {true, "Validation successful."};
}
