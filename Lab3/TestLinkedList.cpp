/******************************************************************************
 * LinkedListTest.cpp
 *
 * This file tests the LinkedList class.
 *
 * Compile:
 *  g++ -std=c++11 -o TestLinkedList TestLinkedList.cpp LinkedList.cpp
 *
 * Then run:
 *  ./TestLinkedList
 ******************************************************************************/

#include <cassert>
#include <iostream>
#include <sstream>
#include "LinkedList.h"

using namespace std;

template <typename F>
inline static void testOutput(F &&lambda, string expected)
{
    ostringstream oss;
    streambuf *oldBuf = cout.rdbuf();
    cout.rdbuf(oss.rdbuf());
    lambda();
    cout.rdbuf(oldBuf);
    assert(oss.str() == expected);
}

void testEmptyList()
{
    LinkedList list;
    // The list should have length 0.
    assert(list.Length() == 0);

    // GetValueAt on an empty list should return an empty string.
    assert(list.GetValueAt(0) == "");
    assert(list.GetValueAt(1) == "");

    // Removing the first element from an empty list should return "".
    assert(list.RemoveFirst() == "");

    // Test PrintList on an empty list.
    testOutput([&]()
               { list.PrintList(); }, "[]\n");
}

void testSingleInsertRemove()
{
    LinkedList list;
    list.InsertFirst("hello");
    assert(list.Length() == 1);
    // The only element should be at index 0.
    assert(list.GetValueAt(0) == "hello");

    // RemoveFirst should return "hello" and leave the list empty.
    assert(list.RemoveFirst() == "hello");
    assert(list.Length() == 0);

    // Removing again should return an empty string.
    assert(list.RemoveFirst() == "");
}

void testMultipleInsertGet()
{
    LinkedList list;
    list.InsertFirst("A"); // List: A
    list.InsertFirst("B"); // List: B, A
    list.InsertFirst("C"); // List: C, B, A

    assert(list.Length() == 3);
    assert(list.GetValueAt(0) == "C");
    assert(list.GetValueAt(1) == "B");
    assert(list.GetValueAt(2) == "A");

    // Test out-of-bound indices.
    assert(list.GetValueAt(3) == "");
    assert(list.GetValueAt(-1) == "");
}

void testMultipleRemove()
{
    LinkedList list;
    list.InsertFirst("A");
    list.InsertFirst("B");
    list.InsertFirst("C"); // List: C, B, A

    // Remove first (should remove "C").
    assert(list.RemoveFirst() == "C");
    assert(list.Length() == 2);
    assert(list.GetValueAt(0) == "B");
    assert(list.GetValueAt(1) == "A");

    // Remove first (should remove "B").
    assert(list.RemoveFirst() == "B");
    assert(list.Length() == 1);
    assert(list.GetValueAt(0) == "A");

    // Remove first (should remove "A", list becomes empty).
    assert(list.RemoveFirst() == "A");
    assert(list.Length() == 0);
    assert(list.RemoveFirst() == "");
}

void testPrintList()
{
    LinkedList list;
    list.InsertFirst("1");
    list.InsertFirst("2");
    list.InsertFirst("3"); // List should be: 3, 2, 1

    testOutput([&]()
               { list.PrintList(); }, "[3,2,1]\n");
}

void testInsertEmptyString()
{
    LinkedList list;
    list.InsertFirst("");
    assert(list.Length() == 1);
    assert(list.GetValueAt(0) == "");
    assert(list.RemoveFirst() == "");
    assert(list.Length() == 0);
}

void testReinsertAfterRemoval()
{
    LinkedList list;
    list.InsertFirst("first");
    list.InsertFirst("second");
    assert(list.RemoveFirst() == "second");
    list.InsertFirst("third");
    assert(list.Length() == 2);
    assert(list.GetValueAt(0) == "third");
    assert(list.GetValueAt(1) == "first");
}

int main()
{
    testEmptyList();
    cout << "testEmptyList passed." << endl;

    testSingleInsertRemove();
    cout << "testSingleInsertRemove passed." << endl;

    testMultipleInsertGet();
    cout << "testMultipleInsertGet passed." << endl;

    testMultipleRemove();
    cout << "testMultipleRemove passed." << endl;

    testPrintList();
    cout << "testPrintList passed." << endl;

    testInsertEmptyString();
    cout << "testInsertEmptyString passed." << endl;

    testReinsertAfterRemoval();
    cout << "testReinsertAfterRemoval passed." << endl;

    cout << "All tests passed successfully." << endl;

    return 0;
}
