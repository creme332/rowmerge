#include "CSVHandler.h"

std::string CSVHandler::readCSV(const std::string &filename) {
  auto validation = isValidCSV(filename);
  if (!validation.first) {
    std::cerr << "Error: " << validation.second << std::endl;
    return "";
  }

  std::ifstream file(filename);
  if (!file) {
    std::cerr << "Error: Unable to open file " << filename << std::endl;
    return "";
  }

  std::stringstream buffer;
  buffer << file.rdbuf(); // Read entire file into buffer
  return buffer.str();
}

bool CSVHandler::writeToFile(const std::string &filename,
                             const std::string &content) {
  std::ofstream file(filename);
  if (!file) {
    std::cerr << "Error: Unable to open file " << filename << " for writing."
              << std::endl;
    return false;
  }

  file << content;
  return true;
}

std::pair<bool, std::string>
CSVHandler::isValidCSV(const std::string &filename) {
  // Check file extension
  if (filename.substr(filename.find_last_of(".") + 1) != "csv") {
    return {false, "File does not have a .csv extension."};
  }

  // Check if file exists and is not empty
  struct stat fileInfo;
  if (stat(filename.c_str(), &fileInfo) != 0) {
    return {false, "File does not exist."};
  }

  if (fileInfo.st_size == 0) {
    return {false, "File is empty."};
  }

  return {true, "File is valid."};
}
