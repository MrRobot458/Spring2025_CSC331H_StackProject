/*
* Purpose: 
*     This is the header file for a Linked List implementation of a Stack class. The C++ language standard is C++20.
* 
* Input: None. 
* Output: None.
*/

#ifndef LINKED_STACK_H
#define LINKED_STACK_H

//---- Node struct definition ----//
template <typename T>
struct Node {
    T info;         // Stores the data contained in the node
    Node<T>* next;  // Pointer to the next node

    // Constructor
    Node(const T& item, Node<T>* nextNode = nullptr) : info(item), next(nextNode) { }
};

//---- LinkedStack class declaration ----//
template <typename T>
class LinkedStack {
private:
    Node<T>* top;  // Pointer to the node at the top of the stack

    // Copies another stack
    void copy(const LinkedStack<T>&);

    // Deletes the entire stack
    void destroy();

public:
    // Constructor
    LinkedStack();

    // Copy constructor
    LinkedStack(const LinkedStack<T>&);

    // Destructor
    ~LinkedStack();

    // Overloads the assignment operator (=)
    const LinkedStack<T>& operator=(const LinkedStack<T>&);

    // Returns the item at the top of the stack through a parameter
    void getTop(T&);

    // Returns true if the stack is empty, false otherwise
    bool isEmpty();

    // Inserts a given item onto the top of the stack
    void push(T);

    // Deletes the item at the top of the stack
    void pop();
};

#endif
