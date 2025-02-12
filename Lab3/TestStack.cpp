/******************************************************************************
 * StackTest.cpp
 *
 * This file tests the Stack class implemented using a linked list.
 *
 * To compile (for example, with g++):
 *     g++ -std=c++11 -o StackTest StackTest.cpp Stack.cpp LinkedList.cpp
 *
 * Then run:
 *     ./StackTest
 *
 ******************************************************************************/

#include <cassert>
#include <sstream>
#include <iostream>
#include "Stack.h"

using namespace std;

/** Helper function to capture and test the output from a lambda.
 *  @param lambda A callable that produces output to cout.
 *  @param expected The expected output string.
 */
template <typename F>
inline static void testOutput(F &&lambda, const string &expected)
{
    ostringstream oss;
    streambuf *oldBuf = cout.rdbuf();
    cout.rdbuf(oss.rdbuf());
    lambda();
    cout.rdbuf(oldBuf);
    assert(oss.str() == expected);
}

void testEmptyStack()
{
    Stack s;
    // The newly created stack should be empty.
    assert(s.IsEmpty() == true);
    // Top and Pop should return empty strings.
    assert(s.Top() == "");
    assert(s.Pop() == "");
}

void testPushPopTop()
{
    Stack s;
    s.Push("first");
    // After one push, the stack should not be empty and top should be "first".
    assert(s.IsEmpty() == false);
    assert(s.Top() == "first");

    s.Push("second");
    // Now top should be "second".
    assert(s.Top() == "second");

    s.Push("third");
    // Now top should be "third".
    assert(s.Top() == "third");

    // Pop should return "third" (LIFO behavior).
    string val = s.Pop();
    assert(val == "third");
    // Now top should be "second".
    assert(s.Top() == "second");

    // Pop again.
    val = s.Pop();
    assert(val == "second");
    // Now top should be "first".
    assert(s.Top() == "first");

    // Pop last element.
    val = s.Pop();
    assert(val == "first");
    // Now the stack should be empty.
    assert(s.IsEmpty() == true);
    // Pop on empty stack returns an empty string.
    assert(s.Pop() == "");
}

void testPrintStack()
{
    Stack s;
    s.Push("first");
    s.Push("second");
    s.Push("third");
    // The expected order printed is from top to bottom:
    // third
    // second
    // first
    testOutput([&]()
               { s.PrintStack(); }, "third\nsecond\nfirst\n");
}

int main()
{
    testEmptyStack();
    cout << "testEmptyStack passed." << endl;

    testPushPopTop();
    cout << "testPushPopTop passed." << endl;

    testPrintStack();
    cout << "testPrintStack passed." << endl;

    cout << "All tests passed successfully." << endl;
    return 0;
}
