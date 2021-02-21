#ifndef STACK_LIST_H
#define STACK_LIST_H 

#include <initializer_list>
#include <iostream>
#include <string>


template <typename T>
class NodeStack {
public:
    T value;
    NodeStack<T>* next;
    template<typename A> friend class Stack;
private:
    NodeStack<T>(T val) {
        value = val;
    }
    NodeStack<T>() {}
};

template <typename T>
class Stack {
private:
    NodeStack<T>* top = NULL;
    int size = 0;
public:
    int Size() { 
        return size; 
    }
    bool IsEmpty() { 
        if (Size() == 0) {
            return true; 
        }
        return false; 
    }
    Stack() { }
    void push(T value){
        NodeStack<T>* node = new NodeStack(value);
        if (top == NULL){
           top = node; 
           top->next = NULL;
        } else {
            node->next = top;
            top = node;
        }
        ++size;
    }
    T pop(){
        if (! IsEmpty()){
            NodeStack<T>* ptr = top;
            T val = ptr->value;
            top = top->next;
            --size;
            delete ptr;
            return val;
        }
        return 0;
    }
    Stack(const std::initializer_list<T>& list){
        for (T elem : list){
            push(elem);
        }
    }

    std::string to_string(){
        std::string out;
        NodeStack<T>* temp = top;
        for (int i = 0; i < size; ++i){
            out = out + std::to_string(temp->value);
            out = out + " ";
            temp = temp->next;
        }
        return out;
    }

    void clear(){
        int n = size;
        for (int i = 0; i < n; ++i){
            pop();
        }
    }

    void operator=(const std::initializer_list<T>& list){
        clear();
        for (T elem : list){
            push(elem);
        }
    }

    void operator<<(T val){
        push(val);
    }

    void operator>> (T &var){
        var = pop();
    }
};

#endif