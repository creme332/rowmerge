#include "validator.h"
#include <iostream>

int main() {
  Validator validator;
  auto result = validator.validate("hello", "world");

  if (!result.first) {
    std::cout << "Validation failed: " << result.second << std::endl;
  } else {
    std::cout << "Validation passed!" << std::endl;
  }

  return 0;
}
