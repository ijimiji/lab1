#ifndef TEST__WORD_CARD_H_
#define TEST__WORD_CARD_H_
#include <string>
using std::string;
class WordCard {
 public:
  WordCard() = default;
  explicit WordCard(string);

  WordCard(WordCard &);
  WordCard &operator=(WordCard other);

  WordCard(WordCard &&) noexcept;
  WordCard &operator=(WordCard &&other) noexcept;

  ~WordCard() = default;

  string GetWord();
  size_t GetCounter();

  void IncCounter();

  bool operator==(WordCard &other);
  bool operator!=(WordCard &other);

  friend bool operator<(WordCard &first, WordCard &second);

 private:
  string word_{};
  size_t counter_{};
};

WordCard::WordCard(string word) {
  counter_ = 1;
  word_ = word;
}

WordCard::WordCard(WordCard &obj) {
  counter_ = obj.counter_;
  word_ = obj.word_;
}

string WordCard::GetWord() {
  return word_;
}

size_t WordCard::GetCounter() {
  return counter_;
}

void WordCard::IncCounter() {
  counter_++;
}

WordCard &WordCard::operator=(WordCard other) {
  counter_ = other.counter_;
  word_ = other.word_;
  return *this;
}

WordCard::WordCard(WordCard &&obj) noexcept {
  counter_ = obj.counter_;
  word_ = obj.word_;
  obj.counter_ = 0;
  obj.word_ = nullptr;
}

WordCard &WordCard::operator=(WordCard &&other) noexcept {
  counter_ = other.counter_;
  word_ = std::move(other.word_);
  return *this;
}

bool WordCard::operator==(WordCard &other) {
  if (word_ == other.word_) {
    return true;
  }
  return false;
}

bool WordCard::operator!=(WordCard &other) {
  if (word_ != other.word_) {
    return true;
  }
  return false;
}

bool operator<(WordCard &first, WordCard &second) {
  if (first.counter_ < second.counter_) {
    return true;
  }
  return false;
}
#endif //TEST__WORD_CARD_H_
