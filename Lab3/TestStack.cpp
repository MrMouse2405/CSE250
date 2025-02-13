/******************************************************************************
 * TestStack.cpp
 *
 *  Created on: Feb 07 2025
 *      Author: OCdt Syed
 *
 *  Implementation details:
 *      This file tests the generic Stack<string> class using various test cases.
 *
 ******************************************************************************/

#include <iostream>
#include <cassert>
#include "Test.h"
#include "Stack.h"

using namespace std;

/**
 * Tests an empty stack.
 * Verifies that a newly created stack is empty and that Top and Pop return an empty optional.
 */
void testEmptyStack() {
    Stack<string> s;
    assert(s.IsEmpty() == true);
    assert(s.Top().value_or("") == "");
    assert(s.Pop().value_or("") == "");
}

/**
 * Tests push, pop, and top operations.
 * Verifies that the stack maintains Last-In-First-Out (LIFO) order.
 */
void testPushPopTop() {
    Stack<string> s;
    s.Push("first");
    assert(s.IsEmpty() == false);
    assert(s.Top().value_or("") == "first");

    s.Push("second");
    assert(s.Top().value_or("") == "second");

    s.Push("third");
    assert(s.Top().value_or("") == "third");

    string val = s.Pop().value_or("");
    assert(val == "third");
    assert(s.Top().value_or("") == "second");

    val = s.Pop().value_or("");
    assert(val == "second");
    assert(s.Top().value_or("") == "first");

    val = s.Pop().value_or("");
    assert(val == "first");
    assert(s.IsEmpty() == true);
    assert(s.Pop().value_or("") == "");
}

/**
 * Tests printing the stack.
 * Verifies that PrintStack outputs the stack contents from top to bottom.
 */
void testPrintStack() {
    Stack<string> s;
    s.Push("first");
    s.Push("second");
    s.Push("third");
    Test::testOutput([&]() {
        s.PrintStack();
    }, "third\nsecond\nfirst\n");
}

/**
 * Runs all Stack tests.
 * Calls each individual test function and prints a message upon successful completion.
 */
void Test::testStack() {
    testEmptyStack();
    cout << "testEmptyStack passed." << endl;

    testPushPopTop();
    cout << "testPushPopTop passed." << endl;

    testPrintStack();
    cout << "testPrintStack passed." << endl;

    cout << "All tests passed successfully." << endl;
}
