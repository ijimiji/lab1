
#ifndef STACK_LIST_H
#define STACK_LIST_H 

#include <initializer_list>
#include <iostream>
#include <string>


template <typename T>
class stack {
private:
    T* arr;
    int capacity = 0;
    int top = 0;

public:
    stack() {}

    ~stack(){
        if (capacity != 0){
            delete[] arr;
        }
    }

    int size() {
        return top;
    }

    bool is_empty() {
        if (size() == 0) {
            return true;
        }
        return false;
    }

    void push(T val) {
        T* tmp = arr;
        // Allocate memory if it's not enough to push one more value
        if (top + 1 > capacity) {
            try {
                arr = new T[capacity + 1];

                for (int i = 0; i < capacity; ++i) {
                    arr[i] = tmp[i];
                }

                if (capacity != 0){
                    delete[] tmp;
                }

                capacity++;
                arr[top] = val;
                top++;
                return;
            }
            catch (std::bad_alloc e) {
                std::cout << e.what() << std::endl;
            }
        }
        arr[top] = val;
        ++top;
    }

    // Pop element, but keep capacity value to preserve some memory in case
    // we want to push anything else
    T pop() {
        if (is_empty()) {
            std::cout << "Stack is empty" << std::endl;
        }
        else {
            top--;
        }
        return arr[top];
    }

    std::string to_string(){
        std::string out = "";
        for (int i = 0; i < top; ++i){
            out = out + std::to_string(arr[i]) + " ";
        }
        return out;
    }

    void operator<<(T val){
        push(val);
    }

    void operator>>(T &var){
        var = pop();
    }

    T operator[](int i){
        if (i > top-1 || i < 0){
            std::cout << i<< "-th element is out of scope" << std::endl;
        } else {
            return arr[i];
        }
    }
    void operator=(const stack<T>&st){
       delete[] arr;
       int N = st.size();
       arr = new T[N];
       for (int i = 0; i<N; ++i){
           push(st[i]);
       }
       capacity = N;
       top = N;
    }
    bool operator<(stack <T>&st){
        if (size() < st.size()){
            return true;
        }
        return false;
    }

    bool operator==(stack <T>&st){
        if (size() == st.size()){
            return true;
        }
        return false;

    }
    T top_elem(){
        return arr[top-1];
    }
};

#endif