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
  return fileContent;
}

std::vector<std::tuple<int, int, std::string>>
findDelphiComments(std::vector<std::string> lines) {
  std::vector<std::tuple<int, int, std::string>> commentsGroups;

  int patternsInGroup = 0;
  int lineNumber;
  std::string pattern;

  std::string line;
  bool previousIsComment = false;
  int n = lines.size();

  for (int i = 0; i < n; line = lines[i], ++i) {
    if (isDelphiComment(line)) {
      if (!previousIsComment) {
        lineNumber = i + 1;
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

std::string recordToString(std::tuple<int, int, std::string> record) {
  std::string stringRecord = "";
  int lineNumber = std::get<0>(record);
  int patternsInGroup = std::get<1>(record);
  std::string pattern = std::get<2>(record);

  stringRecord = stringRecord + pattern;
  stringRecord =
      stringRecord + " | " + "found on line " + std::to_string(lineNumber);
  stringRecord =
      stringRecord + " | occurences: " + std::to_string(patternsInGroup);
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
  auto fileName = selectFile();
  auto fileContent = readFile(fileName);
  auto flattenedFileContent = flattenFileContent(fileContent);
  printFileContent(flattenedFileContent);
  auto delphiComments = findDelphiComments(flattenedFileContent);
  auto outputFileContent = makeFileFromRecords(delphiComments);
  writeFile(outputFileContent);
}

int main() {
  solveTask();
  printFileContent(readFile("output"));
  return 0;
}
