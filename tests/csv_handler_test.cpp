#include "../src/CSVHandler.h"
#include "doctest.h"
#include <fstream>
#include <cstdio> //for remove

void createTestFile(const std::string& filename, const std::string& content) {
    std::ofstream file(filename);
    file << content;
    file.close();
}

TEST_CASE("Valid CSV file") {
    const std::string filename = "test_valid.csv";
    createTestFile(filename, "a,b,c\n1,2,3\n4,5,6\n");
    auto result = CSVHandler::isValidCSV(filename);
    CHECK(result.first == true);
    std::remove(filename.c_str());
}

TEST_CASE("Invalid extension") {
    const std::string filename = "invalid.txt";
    createTestFile(filename, "a,b,c\n1,2,3\n");
    auto result = CSVHandler::isValidCSV(filename);
    CHECK(result.first == false);
    CHECK(result.second.find(".csv extension") != std::string::npos);
    std::remove(filename.c_str());
}

TEST_CASE("Non-existent file is rejected early") {
    const std::string filename = "this_file_does_not_exist.csv";

    auto result = CSVHandler::isValidCSV(filename);
    CHECK(result.first == false);
    CHECK(result.second.find(filename + " does not exist.") != std::string::npos);
}
TEST_CASE("Empty file") {
    const std::string filename = "empty.csv";
    createTestFile(filename, "");
    auto result = CSVHandler::isValidCSV(filename);
    CHECK(result.first == false);
    CHECK(result.second.find("is an empty file") != std::string::npos);
    std::remove(filename.c_str());
}

// TEST_CASE("File that cannot be opened is rejected") {
//     const std::string filename = "nonexistent.csv";

//     auto result = CSVHandler::isValidCSV(filename);
//     CHECK(result.first == false);
//     CHECK(result.second.find("Error: Unable to open file") != std::string::npos);
// }

TEST_CASE("Inconsistent columns") {
    const std::string filename = "bad_columns.csv";
    createTestFile(filename, "a,b,c\n1,2\n3,4,5\n");
    auto result = CSVHandler::isValidCSV(filename);
    CHECK(result.first == false);
    CHECK(result.second==  "Line #2 has 2 columns, but expected 3 columns.");
    std::remove(filename.c_str());
}

TEST_CASE("Duplicate lines") {
    const std::string filename = "duplicate.csv";
    createTestFile(filename, "a,b,c\n1,2,3\n1,2,3\n");
    auto result = CSVHandler::isValidCSV(filename);
    CHECK(result.first == false);
    CHECK(result.second.find("Duplicate line") != std::string::npos);
    std::remove(filename.c_str());
}

TEST_CASE("Only one column") {
    const std::string filename = "one_column.csv";
    createTestFile(filename, "onlyone\nanotherline\n");
    auto result = CSVHandler::isValidCSV(filename);
    CHECK(result.first == false);
    CHECK(result.second.find("only 1 column") != std::string::npos);
    std::remove(filename.c_str());
}

TEST_CASE("CSV with an empty line is rejected") {
    const std::string filename = "empty_line.csv";
    std::string content = "a,b,c\n\n1,2,3\n";
    createTestFile(filename, content);

    auto result = CSVHandler::isValidCSV(filename);
    CHECK(result.first == false);
    CHECK(result.second.find("Line #2 is empty") != std::string::npos);

    std::remove(filename.c_str());
}

