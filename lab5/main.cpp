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
  std::vector<std::string> fileContent;
  do {
    std::cout << "Select file to open:" << std::endl;
    std::cin >> fileName;
    std::cout << "Here is the content of " << fileName << ":" << std::endl;
    fileContent = readFile(fileName);
    printFileContent(fileContent);
    std::cout << "Confirm file selection [y/n]" << std::endl;
    std::cin >> choice;
  } while (choice != "y");
  // Create empty file if it's not present
  if (fileContent.size() == 0) {
    std::ofstream empty_file(fileName);
    empty_file.close();
  }
  return fileName;
}

std::string flattenString(std::string nestedString) {
  // Return string with no blank charactes at the beginning 
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
findDelphiGroups(std::vector<std::string> lines) {
  std::vector<std::tuple<int, int, std::string>> commentsGroups;
  int occurences = 0;
  int lineNumber;
  std::string pattern;
  bool staged = true; // If group is pushed to vector it's staged
  int N = lines.size() - 1;
  int n = 1;
  
  for (auto line : lines) {
    if (isDelphiComment(line)) {
      if (staged) {
        pattern = line;
        lineNumber = n;
        staged = false;
      }

      if (line == pattern) {
        ++occurences;
      } else {
        auto record = std::make_tuple(lineNumber, occurences, pattern);
        commentsGroups.push_back(record);
        staged = false;
        occurences = 1;
        lineNumber = n;
        pattern = line;
      }
      // Check if it's the last line
      if (line == lines[N]) {
        auto record = std::make_tuple(lineNumber, occurences, pattern);
        commentsGroups.push_back(record);
      }
    } else {
      if (!staged) {
        auto record = std::make_tuple(lineNumber, occurences, pattern);
        commentsGroups.push_back(record);
        staged = true;
        occurences = 0;
      }
    }
    ++n;
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
      stringRecord + "\t| " + "found on line " + std::to_string(lineNumber);
  stringRecord =
      stringRecord + "\t| occurences: " + std::to_string(patternsInGroup);
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
  auto delphiComments = findDelphiGroups(flattenedFileContent);
  auto outputFileContent = makeFileFromRecords(delphiComments);
  writeFile(outputFileContent);
}

class App {
public:
  static void Main() {
    solveTask();
    std::cout << "Here is the content of output file" << std::endl;
    printFileContent(readFile("output"));
  }
};

int main() {
  App::Main();
  return 0;
}
