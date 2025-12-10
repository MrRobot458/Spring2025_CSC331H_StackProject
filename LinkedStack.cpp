/*
Purpose:
    This is the implementaion file for a Linked List implementation of a Stack class. The C++ language standard is C++20.

Input: None.
Output: None.
*/

#include "LinkedStack.h"
using namespace std;

//---- LinkedStack class implementation ----//

// Constructor
template <typename T>
LinkedStack<T>::LinkedStack() : top(nullptr) { }

// Copy constructor
template <typename T>
LinkedStack<T>::LinkedStack(const LinkedStack<T>& other) : top(nullptr) {
    copy(other);
}

// Destructor
template <typename T>
LinkedStack<T>::~LinkedStack() {
    destroy();
}

// Overloads the assignment operator (=)
template <typename T>
const LinkedStack<T>& LinkedStack<T>::operator=(const LinkedStack<T>& other) {
    if (this != &other) {
        destroy();
        copy(other);
    }
    return *this;
}

// Copies another stack
template <typename T>
void LinkedStack<T>::copy(const LinkedStack<T>& other) {
    Node<T>* current = nullptr;         // Keeps track of the current node in this stack
    Node<T>* otherCurrent = other.top;  // Keeps track of the current node in the other stack

    if (otherCurrent != nullptr) {
        // Set the current nodes
        top = new Node<T>(otherCurrent->info);
        current = top;
        otherCurrent = otherCurrent->next;

        // Copy nodes from the other stack one by one
        while (otherCurrent != nullptr) {
            current->next = new Node<T>(otherCurrent->info);
            current = current->next;
            otherCurrent = otherCurrent->next;
        }
    }
    return;
}

// Deletes the entire stack
template <typename T>
void LinkedStack<T>::destroy() {
    while (top != nullptr) {
        Node<T>* trash = top;  // Stores the current node to be deleted
        top = top->next;
        delete trash;
    }
    return;
}

// Returns the item at the top of the stack through a parameter
template <typename T>
void LinkedStack<T>::getTop(T& box) {
    if (!isEmpty()) box = top->info;
    return;
}

// Returns true if the stack is empty, false otherwise
template <typename T>
bool LinkedStack<T>::isEmpty() {
    bool check = false;  // Boolean flag for empty stack

    if (top == nullptr) check = true;
    return check;
}

// Inserts a given item onto the top of the stack
template <typename T>
void LinkedStack<T>::push(T item) {
    Node<T>* newNode = nullptr;  // Pointer to the new node being inserted

    newNode = new Node<T>(item);
    newNode->next = top;
    top = newNode;
    return;
}

// Deletes the item at the top of the stack
template <typename T>
void LinkedStack<T>::pop() {
    if (!isEmpty()) {
        Node<T>* trash = top;  // Pointer to the node getting deleted

        top = top->next;
        delete trash;
    }
    return;
}

//---- Declarations to prevent unresolved external symbol(s) linker error (LNK2019) ----//
template class LinkedStack<double>;
template class LinkedStack<int>;
template class LinkedStack<char>;
