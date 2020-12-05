//
// Created by Jahor on 5.12.20.
//

#ifndef TEST__BIDIRECTIONAL_LIST_ON_ARRAY_H_
#define TEST__BIDIRECTIONAL_LIST_ON_ARRAY_H_
#include <initializer_list>
#include "word_card.h"
namespace containers {
template<typename T>
class BiDirectionalList {
 private:
  T *data_;
  size_t size_ = 0;
  size_t capacity_;
  static const size_t MIN_CAPACITY = 10;
  static const size_t GROWTH_FACTOR = 2;
 public:
  BiDirectionalList<T>() {
    data_ = new T[MIN_CAPACITY];
    capacity_ = MIN_CAPACITY;
  }
  BiDirectionalList<T>(std::initializer_list<T> xss) {
    for (auto x : xss) {
      PushBack(x);
    }
  }
  BiDirectionalList<T>(BiDirectionalList<T> &obj) {
    int n = obj.Size();
    capacity_ = obj.capacity_;
    for (int i = 0; i < n; ++i) {
      PushBack(obj[i]);
    }
  }
  BiDirectionalList<T> &operator=(const BiDirectionalList<T> &obj) {
  }

  BiDirectionalList<T>(BiDirectionalList<T> &&obj) noexcept {
    int n = obj.Size();
    capacity_ = obj.capacity_;
    for (int i = n - 1; i != -1; --i) {
      PushBack(obj[i]);
      obj.PopBack();
    }
  }
  BiDirectionalList<T> &operator=(BiDirectionalList<T> &&obj) noexcept {
    int n = obj.Size();
    capacity_ = obj.capacity_;
    for (int i = n - 1; i != -1; --i) {
      PushBack(obj[i]);
      obj.PopBack();
    }
  }
  int Size() {
    return size_;
  }
  bool IsEmpty() {
    if (size_ == 0) {
      return true;
    }
    return false;
  }

  T *Front() {
    if (!IsEmpty()) {
      return data_;
    } else {
      throw std::exception();
    }
  }
  T *Back() {
    if (!IsEmpty()) {
      return data_ + size_;
    } else {
      throw std::exception();
    }
  }
  std::vector<T> ToVector() {
    std::vector<T> temp;
    for (int i = 0; i < size_; ++i) {
      temp.push_back(data_[i]);
    }
    return temp;
  }
  void PushFront(const T &value) {
    T *temp;
    if (size_ + 1 > capacity_) {
      temp = new T[capacity_ * GROWTH_FACTOR];
      capacity_ = capacity_ * GROWTH_FACTOR;
    } else {
      temp = new T[capacity_];
    }
    temp[0] = value;
    for (int i = 0; i < size_; ++i) {
      temp[i + 1] = data_[i];
    }
    delete[] data_;
    data_ = temp;
    ++size_;
  }

  void PushBack(const T &value) {
    T *temp;
    if (size_ + 1 > capacity_) {
      temp = new T[capacity_ * GROWTH_FACTOR];
      capacity_ = capacity_ * GROWTH_FACTOR;
      for (int i = 0; i < size_; ++i) {
        temp[i] = data_[i];
      }
      delete[] data_;
      data_ = temp;
    }
    data_[size_] = value;
    ++size_;
  }
  void PushFront(T &&value) {
    T *temp;
    if (size_ + 1 > capacity_) {
      temp = new T[capacity_ * GROWTH_FACTOR];
      capacity_ = capacity_ * GROWTH_FACTOR;
    } else {
      temp = new T[capacity_];
    }
    temp[0] = (std::move(value));
    for (int i = 0; i < size_; ++i) {
      temp[i + 1] = data_[i];
    }
    delete[] data_;
    data_ = temp;
    ++size_;
  }
  void PushBack(T &&value) {
    T *temp;
    if (size_ + 1 > capacity_) {
      temp = new T[capacity_ * GROWTH_FACTOR];
      capacity_ = capacity_ * GROWTH_FACTOR;
      for (int i = 0; i < size_; ++i) {
        temp[i] = data_[i];
      }
      delete[] data_;
      data_ = temp;
    }
    data_[size_] = (std::move(value));
    ++size_;
  }

  T PopFront() {
    if (!IsEmpty()) {
      T temp = data_[0];
      for (int i = 1; i < size_; ++i) {
        data_[i - 1] = data_[i];
      }
      --size_;
      return temp;
    }
    throw std::exception();
  }
  T PopBack() {
    if (!IsEmpty()) {
      --size_;
      return data_[size_];
    }
    throw std::exception();
  }
  void InsertBefore(size_t index, const T &value) {
    if (index == 0) {
      throw std::exception();
    }
    if (size_ + 1 > capacity_) {
      T *temp = new T[capacity_ * GROWTH_FACTOR];
      capacity_ = capacity_ * GROWTH_FACTOR;
      for (int i = 0; i < index; ++i) {
        temp[i] = data_[i];
      }
      temp[index] = value;
      for (int i = index; i < size_; ++i) {
        temp[i + 1] = data_[i];
      }
    } else {

      for (int i = size_ - 1; i >= index; --i) {
        data_[i + 1] = data_[i + 1];
      }
      data_[index] = value;
    }
    ++size_;

  }
  void InsertAfter(size_t index, const T &value) {
    if (index == 0) {
      throw std::exception();
    }
    if (size_ + 1 > capacity_) {
      T *temp = new T[capacity_ * GROWTH_FACTOR];
      capacity_ = capacity_ * GROWTH_FACTOR;
      for (int i = 0; i <= index; ++i) {
        temp[i] = data_[i];
      }
      temp[index + 1] = value;
      for (int i = index + 1; i < size_; ++i) {
        temp[i + 1] = data_[i];
      }
    } else {

      for (int i = size_ - 1; i != index; --i) {
        data_[i + 1] = data_[i + 1];
      }
      data_[index + 1] = value;
    }
    ++size_;
  }

  int Find(const T &value) {
    if (IsEmpty()) {
      throw std::exception();
    }
    for (int i = 0; i < size_; ++i) {
      if (data_[i] == value) {
        return i;
      }
    }
    return -1;
  }

  std::vector<int> FindAll(const T &value) {
    std::vector<int> iss;
    if (IsEmpty()) {
      throw std::exception();
    }
    for (int i = 0; i < size_; ++i) {
      if (data_[i] == value) {
        iss.push_back(i);
      }
    }
    return iss;
  }
  T &operator[](int index) {
    if (index > size_ - 1) {
      throw std::exception();
    }
    return data_[index];
  }
  const T &operator[](int index) const {
    if (index > size_ - 1) {
      throw std::exception();
    }
    return *(data_ + index);
  }
  bool operator==(const BiDirectionalList<T> &other) {
    if (other.size_ == size_) {
      for (int i = 0; i < size_; ++i) {
        if (data_[i] != other[i]) {
          return false;
        }
        return true;
      }
    } else {
      return false;
    }
  }
  void Erase(size_t index) {
    if (index > size_ - 1) {
      throw std::exception();
    } else {
      for (int i = size_; i > index; --i) {
        data_[i] = data_[i - 1];
      }
    }
    --size_;
  }
};
}
#endif //TEST__BIDIRECTIONAL_LIST_ON_ARRAY_H_
