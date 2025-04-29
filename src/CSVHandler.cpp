#include "CSVHandler.h"
#include <filesystem>
#include <fstream>
#include <sstream>
#include <unordered_set>

std::string CSVHandler::readFile(const std::string &filename) {
  std::ifstream file(filename, std::ios::binary); // Use binary mode to handle
                                                  // all newline types correctly
  std::string content;

  if (!file) {
    std::cerr << "Error opening file: " << filename << std::endl;
    return "";
  }

  char ch;
  while (file.get(ch)) {
    if (ch == '\r') {
      // Skip carriage return (CR)
      continue;
    } else if (ch == '\n') {
      // Normalize newline
      content += '\n';
    } else {
      content += ch;
    }
  }

  return content;
}

bool CSVHandler::writeToFile(const std::string &filename,
                             const std::string &content) {
  std::ofstream file(
      filename, std::ios::binary); // Use binary to prevent newline translation

  if (!file) {
    std::cerr << "Error opening file for writing: " << filename << std::endl;
    return false;
  }

  file.write(content.c_str(), content.size());
  return true;
}

std::vector<std::vector<std::string>>
CSVHandler::stringToVector(const std::string &str) {
  std::vector<std::vector<std::string>> result;
  std::istringstream stream(str);
  std::string line;

  while (std::getline(stream, line)) { // Read each line
    // ignore empty lines
    if (line.empty())
      continue;

    std::vector<std::string> row;
    std::istringstream lineStream(line);
    std::string cell;

    while (std::getline(lineStream, cell, ',')) { // Split by commas
      row.push_back(cell);
    }

    result.push_back(row);
  }

  return result;
}

std::vector<std::vector<std::string>>
CSVHandler::readCSVAsVector(const std::string &filename) {
  return stringToVector(readFile(filename));
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
    return {false, filename + " is an empty file."};
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
    // Strip trailing carriage return if present (handles \r\n)
    if (!line.empty() && line.back() == '\r') {
      line.pop_back();
    }

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

  if (expectedColumnCount == 1) {
    return {false,
            "File contains only 1 column. Ensure that commas are used to "
            "separate values."};
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
