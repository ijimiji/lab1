#ifndef TEST__FILE_READER_H_
#define TEST__FILE_READER_H_
#include <fstream>
#include <vector>
#include <string>

using std::vector;
using std::string;

class FileReader {
 public:
  vector<string> ReadLines(const string &file_path);
  vector<string> ReadWords(const string &file_path);
};

vector<string> FileReader::ReadLines(const string &file_path) {
  std::ifstream input(file_path);
  vector<string> lines;
  std::string line;
  while (std::getline(input, line)) {
    lines.push_back(line);
  }
  return lines;
}
vector<string> FileReader::ReadWords(const string &file_path) {
  std::ifstream input(file_path);
  vector<string> words;
  std::string word;
  while (input >> word) {
    words.push_back(word);
  }
  return words;
}
#endif //TEST__FILE_READER_H_
