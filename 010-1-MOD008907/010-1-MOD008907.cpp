// 010-1-MOD008907.cpp : This file contains PART 3
#include <iostream>
#include <stack>
#include <string>
using namespace std;

// All Parts: precedence calculator
int precedence(char opChar) {
  if (opChar == '/' || opChar == '*') return 2;
  if (opChar == '+' || opChar == '-') return 1;
  if (opChar == '^') return 3;
  return 0;
}


/// IN-CLASS TEST ANSWERS ///

// Part 3: Infix to Postfix Converter with Linked List Stack

// Linked List Node
template<typename T>  // Allow for creating linked lists containing any type (kind of like string[] int[] etc)
class Node {
public:
  // Node item value
  T value;
  // next node in LinkedStack
  Node* next;

  Node(T initValue) {
    // Set Node initial value.
    this->value = initValue;
    // Set next value to nullptr (assuming node is top of LinkedStack)
    this->next = nullptr;
  }
};

// Stack using Linked List Implementation
// Allow for creating linked lists containing any type (kind of like string[] int[] etc)
template<typename T>
class LinkedStack {
  // Linked List Head
  Node<T>* head;

public:
  // new LinkedStack initiator.
  LinkedStack() { this->head = nullptr; };

  bool isEmpty() {
    // Return true or false depending on if this->head is empty.
    return this->head == nullptr;
  }

  T peak() {
    // If the LinkedStack is NOT empty:
    if (!this->isEmpty()) {
      // Return the top element in the list stored in this->head.
      return this->head->value;
    }
    // Otherwise:
    else {
      // return an empty value of the LinkedList template typename.
      return 0;
    }
  }

  void push(T value) {
    // Define the new node that will be pushed to the LinkedStack.
    Node<T>* newNode = new Node<T>(value);

    // If the new node failed to define properly:
    if (!newNode) {
      // Throw a Stack Overflow (no way website reference) error.
      throw runtime_error("LinkedStack: Stack Overflow on Push()");
    }

    // Set the next value in the new node to the current head node.
    newNode->next = this->head;
    // Set the head node to the new node.
    this->head = newNode;
  }

  void pop() {
    //If the LinkedStack is empty :
    if (this->isEmpty()) {
      // Throw a Stack Underflow error.
      throw runtime_error("LinkedStack: Stack Underflow on Pop()");
    }

    // Otherwise:
    // Define a temp link to the Node so we can delete it after head is redefined.
    Node<T>* tempNode = this->head;
    // Set head to the previous node.
    head = head->next;
    // Delete old head from memory.
    delete tempNode;
  }

  string print(char join[]) {
    // Define a temp link to the Node so we can read the values.
    Node<T>* tempNode = this->head;
    string output = "";

    //While the tempNode is not empty:
    while (tempNode != nullptr) {
      //Print the value of the current node.
      output += tempNode->value;
      // add the join character to the output.
      output += join;
      //Set the tempNode to the next node.
      tempNode = tempNode->next;
    }

    // reverse the string.
    return output;
  }
};

LinkedStack<char> infixToPostfixPart3(string infix) {
  // Create an empty linked list stack for operators
  LinkedStack<char> charStack;
  // Create an empty linked list stack for output
  LinkedStack<char> output;

  // For each character(token) in the infix expression :
  for (char currChar : infix) {
    // If Operand append
    if (isalnum(currChar)) {
      output.push(currChar);
    }
    // If '(' push to stack
    else if (currChar == '(') {
      charStack.push(currChar);
    }
    // If ')' pop until '(' then pop '('
    else if (currChar == ')') {
      while (!charStack.isEmpty() && charStack.peak() != '(') {
        output.push(charStack.peak());
        charStack.pop();
      }
      charStack.pop(); // Remove '('
    }
    // If Operator
    else {
      // pop push until precedence is less than current operator.
      while (!charStack.isEmpty() && precedence(charStack.peak()) >= precedence(currChar)) {
        output.push(charStack.peak());
        charStack.pop();
      }
      charStack.push(currChar);
    }
  }

  // pop operators from stack and push to postfix
  while (!charStack.isEmpty()) {
    output.push(charStack.peak());
    charStack.pop();
  }

  return output;
}

int main() {
  string infix;
  // User input 
  cout << "Enter a infix: ";
  getline(cin, infix);

  // Strip invalid characters
  char chars[] = " ";
  for (unsigned int i = 0; i < strlen(chars); ++i)
  {
    infix.erase(std::remove(infix.begin(), infix.end(), chars[i]), infix.end());
  }

  LinkedStack<char> postfix; // define linked list stack for postfix

  // Attempt to convert infix to postfix
  try {
    postfix = infixToPostfixPart3(infix);
  }
  catch (const exception& e) {
    cerr << "Exception caught: " << e.what() << endl;
  }

  // Output postfix
  cout << "Postfix: ";
  char join[] = "";
  string out = postfix.print(join);
  reverse(out.begin(), out.end());
  cout << out << endl;
  cout << endl; 
  return 0;
}