/******************************************************************************
 * TestLinkedList.cpp
 *
 *  Created on: Feb 07 2025
 *      Author: OCdt Syed
 *
 *  Implementation details:
 *      Tests the LinkedList<string> class using various scenarios.
 *
 ******************************************************************************/

#include <cassert>
#include <iostream>
#include "Test.h"
#include "LinkedList.h"

using namespace std;

/**
 * Tests an empty list.
 * Verifies that an empty list has length 0, returns empty values for GetValueAt and RemoveFirst,
 * and prints as "[]".
 */
void testEmptyList() {
    LinkedList<string> list;
    /** The list should have length 0. */
    assert(list.Length() == 0);

    /** GetValueAt on an empty list should return an empty string. */
    assert(list.GetValueAt(0).value_or("").empty());
    assert(list.GetValueAt(1).value_or("").empty());

    /** Removing the first element from an empty list should return an empty string. */
    assert(list.RemoveFirst().value_or("").empty());

    /** Test PrintList on an empty list. */
    Test::testOutput([&]() { list.PrintList(); }, "[]\n");
}

/**
 * Tests insertion and removal of a single element.
 * Verifies that after inserting one element the list has length 1, the element can be retrieved,
 * and that removal returns the correct element and empties the list.
 */
void testSingleInsertRemove() {
    LinkedList<string> list;
    list.InsertFirst("hello");
    /** The list should now have length 1. */
    assert(list.Length() == 1);
    /** The only element should be at index 0. */
    assert(list.GetValueAt(0).value_or("") == "hello");

    /** RemoveFirst should return "hello" and leave the list empty. */
    assert(list.RemoveFirst().value_or("") == "hello");
    assert(list.Length() == 0);

    /** Removing again should return an empty string. */
    assert(list.RemoveFirst().value_or("") == "");
}

/**
 * Tests multiple insertions and retrieval of values.
 * Inserts three elements and verifies the order, and confirms that out-of-bound indices return empty.
 */
void testMultipleInsertGet() {
    LinkedList<string> list;
    list.InsertFirst("A"); // List becomes: A
    list.InsertFirst("B"); // List becomes: B, A
    list.InsertFirst("C"); // List becomes: C, B, A

    /** Verify that the list has three elements. */
    assert(list.Length() == 3);
    /** Verify the values at each index. */
    assert(list.GetValueAt(0).value_or("") == "C");
    assert(list.GetValueAt(1).value_or("") == "B");
    assert(list.GetValueAt(2).value_or("") == "A");

    /** Test out-of-bound indices. */
    assert(list.GetValueAt(3).value_or("").empty());
    /** Testing a negative index by casting -1 to size_t (should be out-of-bounds). */
    assert(list.GetValueAt(static_cast<size_t>(-1)).value_or("").empty());
}

/**
 * Tests multiple removals.
 * Inserts three elements then removes them one by one, verifying the correct order and list length.
 */
void testMultipleRemove() {
    LinkedList<string> list;
    list.InsertFirst("A");
    list.InsertFirst("B");
    list.InsertFirst("C"); // List becomes: C, B, A

    /** Remove first (should remove "C"). */
    assert(list.RemoveFirst().value_or("") == "C");
    assert(list.Length() == 2);
    assert(list.GetValueAt(0).value_or("") == "B");
    assert(list.GetValueAt(1).value_or("") == "A");

    /** Remove first (should remove "B"). */
    assert(list.RemoveFirst().value_or("") == "B");
    assert(list.Length() == 1);
    assert(list.GetValueAt(0).value_or("") == "A");

    /** Remove first (should remove "A", leaving the list empty). */
    assert(list.RemoveFirst().value_or("") == "A");
    assert(list.Length() == 0);
    /** Further removal should yield an empty string. */
    assert(list.RemoveFirst().value_or("").empty());
}

/**
 * Tests the PrintList function.
 * Inserts three elements and verifies that PrintList outputs the expected string.
 */
void testPrintList() {
    LinkedList<string> list;
    list.InsertFirst("1");
    list.InsertFirst("2");
    list.InsertFirst("3"); // List should be: 3,2,1

    /** Verify that PrintList produces the expected output. */
    Test::testOutput([&]() { list.PrintList(); }, "[3,2,1]\n");
}

/**
 * Tests inserting an empty string.
 * Verifies that an empty string can be inserted and removed, and that the list behaves correctly.
 */
void testInsertEmptyString() {
    LinkedList<string> list;
    list.InsertFirst("");
    /** The list should contain one element (an empty string). */
    assert(list.Length() == 1);
    /** Verify that the element is empty. */
    assert(list.GetValueAt(0).value_or("").empty());
    /** Removal should yield an empty string. */
    assert(list.RemoveFirst().value_or("").empty());
    assert(list.Length() == 0);
}

/**
 * Tests reinsertion after removal.
 * Inserts two elements, removes one, then inserts another and verifies the final order.
 */
void testReinsertAfterRemoval() {
    LinkedList<string> list;
    list.InsertFirst("first");
    list.InsertFirst("second");
    /** Removing the first element should remove "second". */
    assert(list.RemoveFirst().value_or("") == "second");
    list.InsertFirst("third");
    /** The list should now contain two elements with the expected order. */
    assert(list.Length() == 2);
    assert(list.GetValueAt(0).value_or("") == "third");
    assert(list.GetValueAt(1).value_or("") == "first");
}

/**
 * Runs all LinkedList tests.
 * Calls each test function and prints a message upon successful completion.
 */
void Test::testLinkedList() {
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
}
