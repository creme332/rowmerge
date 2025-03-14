#include "CSVHandler.h"

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

/**
 * @brief Reads a CSV file and parses its contents into a vector of rows,
 *        where each row is represented as a vector of strings (columns).
 *
 * @param filename The path to the CSV file.
 * @return A vector of rows, where each row is a vector of strings representing
 * the columns.
 * @throws std::runtime_error If the file cannot be opened.
 *
 * @note This function assumes that the CSV file uses commas (`,`) as the
 * delimiter. It does not handle quoted values or escape characters.
 */
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

  return {true, filename + " is valid."};
}
