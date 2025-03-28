#include "CSVHandler.h"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <unordered_set>

std::string CSVHandler::readCSVAsString(const std::string &filename) {
  auto validation = isValidCSV(filename);
  if (!validation.first) {
    std::cerr << "Error: " << validation.second << std::endl;
    return "";
  }

  std::ifstream file(filename);
  if (!file || !file.is_open()) {
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

std::vector<std::vector<std::string>>
CSVHandler::readCSVAsVector(const std::string &filename) {
  std::vector<std::vector<std::string>> data;
  std::ifstream file(filename);

  // Check if the file opened successfully
  if (!file || !file.is_open()) {
    throw std::runtime_error("Could not open file: " + filename);
  }

  std::string line;
  // Read the file line by line
  while (std::getline(file, line)) {
    std::vector<std::string> row;
    std::stringstream ss(line);
    std::string cell;

    // Split the line by commas and store in row vector
    while (std::getline(ss, cell, ',')) {
      row.push_back(cell);
    }

    // Add the parsed row to the data vector
    data.push_back(row);
  }

  return data;
}

std::pair<bool, std::string>
CSVHandler::isValidCSV(const std::string &filename) {
  // Check file extension
  if (filename.substr(filename.find_last_of(".") + 1) != "csv") {
    return {false, "File " + filename + " does not have a .csv extension."};
  }

  // Check if file exists and is not empty
  struct stat fileInfo;
  if (stat(filename.c_str(), &fileInfo) != 0) {
    return {false, "File " + filename + " does not exist."};
  }

  if (fileInfo.st_size == 0) {
    return {false, filename + " is empty."};
  }

  // Open the file
  std::ifstream file(filename);
  if (!file) {
    return {false, "Error: Unable to open file " + filename};
  }

  std::unordered_set<std::string> lines;
  std::string line;
  size_t expectedColumnCount = 0;
  bool firstLineFlag = true;
  int lineNumber = 1;

  // Read the file line by line
  while (std::getline(file, line)) {
    // Reject empty line
    if (line.empty()) {
      return {false, "Line #" + std::to_string(lineNumber) + " is empty."};
    }

    // Check for duplicate lines
    if (lines.find(line) != lines.end()) {
      return {false, "Duplicate line #" + std::to_string(lineNumber) +
                         " found: " + line};
    }
    lines.insert(line);

    // Column consistency check
    std::stringstream lineStream(line);
    size_t columnCount = 0;
    std::string cell;

    while (std::getline(lineStream, cell, ',')) {
      columnCount++;
    }

    // For the first line, set the expected column count
    if (firstLineFlag) {
      expectedColumnCount = columnCount;
      firstLineFlag = false;
    } else {
      // Check if the current line matches the expected column count
      if (columnCount != expectedColumnCount) {
        return {false, "Line #" + std::to_string(lineNumber) + " has " +
                           std::to_string(columnCount) +
                           " columns, but expected " +
                           std::to_string(expectedColumnCount) + " columns."};
      }
    }

    lineNumber++;
  }

  // If no issues are found, return success
  return {true, filename + " is valid."};
}

std::string CSVHandler::generate(const int rows, const int cols) {
  std::srand(std::time(nullptr));
  std::stringstream ss;
  std::unordered_set<std::string> uniqueLines;

  for (int i = 0; i < rows; ++i) {

    std::string line;

    for (int j = 0; j < cols; ++j) {
      int num = std::rand() % 100 + 1; // Random number between 1 and 100
      line += std::to_string(num);
      if (j < cols - 1)
        line += ",";
    }

    // Ensure uniqueness of each line
    if (uniqueLines.find(line) == uniqueLines.end()) {
      uniqueLines.insert(line);
      ss << line << "\n";
    } else {
      --i; // Regenerate the line if it's not unique
    }
  }

  // Return the generated CSV as a string
  return ss.str();
}
