#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

bool isDelphiComment(std::string line) {
    if (line[0] == '/' && line[1] == '/')
        return true;
    return false;
}

std::string trimDelphiComment(std::string comment) {
    std::string trimmedComment = "";
    int n = comment.length();
    for (int i = 2; i < n; ++i) {
        trimmedComment = trimmedComment + comment[i];
    }
    return trimmedComment;
}

std::vector<std::string> readFile(std::string fileName) {
    std::ifstream inputFile(fileName);
    std::string line;
    std::vector<std::string> lines;
    if (inputFile.is_open())
        while (std::getline(inputFile, line)) {
            lines.push_back(line);
        }
    return lines;
}

void printFileContent(std::vector<std::string> fileContent) {
    if (fileContent.size() == 0) {
        std::cout << "[FILE IS EMPTY]" << std::endl;
    } else {
        for (std::string line : fileContent) {
            std::cout << line << std::endl;
        }
    }
}

std::string selectFile() {
    std::string fileName, choice;
    do {
        std::cout << "Select file to open:" << std::endl;
        std::cin >> fileName;
        std::cout << "Here is content of " << fileName << ":" << std::endl;
        printFileContent(readFile(fileName));
        std::cout << "Confirm file selection [y/n]" << std::endl;
        std::cin >> choice;
    } while (choice != "y");
    return fileName;
}

std::string flattenString(std::string nestedString) {
    std::stringstream ss(nestedString);
    std::string string = "";
    std::string temp;
    while (ss >> temp) {
        string = string + ((string == "") ? "" : " ") + temp;
    }
    return string;
}

std::vector<std::string>
flattenFileContent(std::vector<std::string> fileContent) {
    int n = fileContent.size();
    for (int i = 0; i < n; ++i) {
        fileContent[i] = flattenString(fileContent[i]);
    }
    fileContent.push_back("\n");
    return fileContent;
}

std::vector<std::tuple<int, int, std::string>>
findDelphiComments(std::vector<std::string> lines) {
    // std::tuple<int, int, std::string> commentsGroup;
    std::vector<std::tuple<int, int, std::string>> commentsGroups;
    bool previousIsComment = false;
    int patternsInGroup = 0;
    int lineNumber;
    std::string pattern;
    int n = lines.size();

    std::string line;
    for (int i = 0; i < n; ++i, line = lines[i]) {
        if (isDelphiComment(line)) {
            if (!previousIsComment) {
                lineNumber = i;
                pattern = line;
            };
            ++patternsInGroup;

            previousIsComment = true;
        } else {
            if (previousIsComment) {
                commentsGroups.push_back(
                    std::make_tuple(lineNumber, patternsInGroup, pattern));
                patternsInGroup = 0;
            }
            previousIsComment = false;
        }
    }
    return commentsGroups;
}

std::string convertToString(std::string x) { return x; }

std::string convertToString(int x) { return std::to_string(x); }

// enum RecordFild { repeatingString = 1,  }
// std::string makeRecord(std::vector<std::string>) {}

std::string recordToString(std::tuple<int, int, std::string> record) {
    std::string stringRecord = "";
    auto [lineNumber, patternsInGroup, pattern] = record;
    stringRecord = stringRecord + pattern;
    stringRecord =
        stringRecord + " | " + "found on line " + std::to_string(lineNumber);
    stringRecord =
        stringRecord + " | " + std::to_string(patternsInGroup) + " occurences";
    stringRecord = stringRecord + '\n';
    return stringRecord;
}

std::vector<std::string>
makeFileFromRecords(std::vector<std::tuple<int, int, std::string>> records) {
    std::vector<std::string> fileContent;
    for (auto record : records) {
        fileContent.push_back(recordToString(record));
    }
    return fileContent;
}

void writeFile(std::vector<std::string> lines) {
    std::ofstream outputFile("output");
    for (std::string line : lines) {
        outputFile << line;
    }
}

void solveTask() {
    writeFile(makeFileFromRecords(
        findDelphiComments(flattenFileContent(readFile(selectFile())))));
}

int main() {
    solveTask();
    printFileContent(readFile("output"));
    return 0;
}
