//
// Created by Jahor on 5.12.20.
//

#ifndef TEST__VOCABULARY_H_
#define TEST__VOCABULARY_H_
#include "file_reader.h"
#include "word_card.h"
#include "bidirectional_list_on_array.h"
#include <string>
#include <map>
class Vocabulary {
 public:
  WordCard *ConvertStringToWordCard(std::string str) {
    auto *wordCard = new WordCard(str);
    return wordCard;
  }
  void ReadFileToCards(std::string file_path) {
    FileReader reader;
    auto words = reader.ReadWords(file_path);
    for (const auto &word : words) {
      listWordCards_.PushBack(ConvertStringToWordCard(word));
    }
  }

  void MakeFrequencyVocab() {
    int n = listWordCards_.Size();
    std::string tempWord;
    for (int i = 0; i < n; ++i) {
      auto ref = listWordCards_[i];
      for (int j = i; j < n; ++j) {
        auto word = listWordCards_[j];
        if (*ref == *word) {
          delete word;
          ref->IncCounter();
          listWordCards_.Erase(j);
        }
      }
    }
  }
  void SortWords() {
    int n = listWordCards_.Size();
    for (int i = 0; i < n; ++i) {
      auto ref = listWordCards_[i];
      auto cmp = listWordCards_[i + 1];
      if (*cmp < *ref) {
        auto temp = ref;
        listWordCards_[i] = cmp;
        listWordCards_[i + 1] = ref;
      }
    }
  }
  std::map<std::string, size_t> CopyToMap() {
    int n = listWordCards_.Size();
    std::map<std::string, size_t> tempMap;
    for (int i = 0; i < n; ++i) {
      tempMap[listWordCards_[i]->GetWord()] = listWordCards_[i]->GetCounter();
    }
    return tempMap;
  }

 private:
  containers::BiDirectionalList<WordCard *> listWordCards_;

};

#endif //TEST__VOCABULARY_H_
