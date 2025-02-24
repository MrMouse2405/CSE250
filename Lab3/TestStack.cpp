/******************************************************************************
 * TestStack.cpp
 *
 *  Created on: Feb 07 2025
 *      Author: OCdt Syed
 *
 *  Implementation details:
 *      This file tests the Stack using various test cases.
 *
 ******************************************************************************/

#include <iostream>
#include "Test.h"
#include "Stack.h"

using namespace std;

void testEmptyStack() {
    Stack<string> s;
    cout << "Stack should be empty: " << (s.IsEmpty() ? "true" : "false") << endl;
    cout << "Top of empty stack: " << s.Top().value_or("<empty>") << endl;
    cout << "Pop from empty stack: " << s.Pop().value_or("<empty>") << endl;
}

void testPushPopTop() {
    Stack<string> s;
    s.Push("first");
    cout << "Stack should not be empty: " << (s.IsEmpty() ? "true" : "false") << endl;
    cout << "Top element: " << s.Top().value_or("<empty>") << endl;

    s.Push("second");
    cout << "Top element after push: " << s.Top().value_or("<empty>") << endl;

    s.Push("third");
    cout << "Top element after push: " << s.Top().value_or("<empty>") << endl;

    cout << "Popping: " << s.Pop().value_or("<empty>") << endl;
    cout << "New top element: " << s.Top().value_or("<empty>") << endl;

    cout << "Popping: " << s.Pop().value_or("<empty>") << endl;
    cout << "New top element: " << s.Top().value_or("<empty>") << endl;

    cout << "Popping: " << s.Pop().value_or("<empty>") << endl;
    cout << "Stack should be empty: " << (s.IsEmpty() ? "true" : "false") << endl;
    cout << "Pop from empty stack: " << s.Pop().value_or("<empty>") << endl;
}

void testPrintStack() {
    Stack<string> s;
    s.Push("first");
    s.Push("second");
    s.Push("third");
    cout << "Expected output from PrintStack: \nthird\nsecond\nfirst" << endl;
    s.PrintStack();
}

void Test::testStack() {
    testEmptyStack();
    testPushPopTop();
    testPrintStack();
}
