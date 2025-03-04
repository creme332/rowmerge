#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <string>
#include <utility> // for std::pair

class Validator {
public:
    std::pair<bool, std::string> validate(const std::string& str1, const std::string& str2);
};

#endif // VALIDATOR_H
