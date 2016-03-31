
#include "CommonDataTypes.h"
#include <stdio.h>
#include "stdafx.h"
#include <iostream>
#include <algorithm>

using namespace::std;

/*
Design a stack that supports push, pop, top, and retrieving the minimum element in constant time.
• push(x) -- Push element x onto stack.
• pop() -- Removes the element on top of the stack.
• top() -- Get the top element.
• getMin() -- Retrieve the minimum element in the stack.
*/


class Node {
public:
    int _data;
    Node *next;
    Node() { 
        _data = 0; next = nullptr; 
    }
    Node(int data) {
        _data = data; next = nullptr;
    }
};

class Stack {
    private:
        Node *head;
    public:
        Stack() {
            head = nullptr;
        }
        void push(int x) {
            Node *temp = new Node(x);
            if (head == nullptr) {
                head = temp;
            }
            temp->next = head;
            head = temp;
        }
        void pop() {
            if (head == nullptr) {
                return;
            }
            Node *temp = head;
            head = head->next;
            delete temp;
        }
        int top() {
            if (head != nullptr)
                return head->_data;
            else
                return UINT_MAX;
        }
        bool isEmpty() {
            return (head == nullptr);
        }
};


class MinStack : Stack {
private:
    Stack *min;
public:
    MinStack() {
        min = new Stack();
    }
    ~MinStack() {
        delete min;
    }
    void push(int x) {
        //push both values if this stack is empty
        if (isEmpty()) {
            Stack::push(x);
            min->push(x);
        }
        else {
            Stack::push(x);
            // if the value being pushed is less than the value on top of the minstack, push it on
            if (x < min->top())
                min->push(x);
            else
                min->push(min->top());
        }
    } 
    void pop() {        
        Stack::pop();
        min->pop();
    }
    int getMin() {
        return min->top();
    }
};

/*
int _tmain(int argc, _TCHAR* argv[])
{

    MinStack ms;

    ms.push(30);
    ms.push(20);
    ms.push(10);

    cout << ms.getMin() << endl;

    ms.push(5);

    cout << ms.getMin() << endl;

    return 0;


}
*/