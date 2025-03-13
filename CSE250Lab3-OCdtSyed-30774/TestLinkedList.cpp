/******************************************************************************
 * TestLinkedList.cpp
 *
 *  Created on: Feb 07 2025
 *      Author: OCdt Syed
 *
 *  Implementation details:
 *      Tests the LinkedLists using various scenarios.
 *
 ******************************************************************************/

#include <iostream>
#include "Test.h"
#include "LinkedList.h"

using namespace std;

void testEmptyList() {
    LinkedList<string> list;
    cout << "The list should have length 0: " << list.Length() << endl;
    cout << "GetValueAt(0): " << list.GetValueAt(0).value_or("<empty>") << endl;
    cout << "GetValueAt(1): " << list.GetValueAt(1).value_or("<empty>") << endl;
    cout << "RemoveFirst: " << list.RemoveFirst().value_or("<empty>") << endl;
    cout << "Expected output from PrintList: []" << endl;
    list.PrintList();
}

void testSingleInsertRemove() {
    LinkedList<string> list;
    list.InsertFirst("hello");
    cout << "The list should have length 1: " << list.Length() << endl;
    cout << "GetValueAt(0): " << list.GetValueAt(0).value_or("<empty>") << endl;
    cout << "RemoveFirst: " << list.RemoveFirst().value_or("<empty>") << endl;
    cout << "The list should have length 0: " << list.Length() << endl;
    cout << "RemoveFirst again: " << list.RemoveFirst().value_or("<empty>") << endl;
}

void testMultipleInsertGet() {
    LinkedList<string> list;
    list.InsertFirst("A");
    list.InsertFirst("B");
    list.InsertFirst("C");
    cout << "The list should have length 3: " << list.Length() << endl;
    cout << "GetValueAt(0): " << list.GetValueAt(0).value_or("<empty>") << endl;
    cout << "GetValueAt(1): " << list.GetValueAt(1).value_or("<empty>") << endl;
    cout << "GetValueAt(2): " << list.GetValueAt(2).value_or("<empty>") << endl;
    cout << "GetValueAt(3) (out of bounds): " << list.GetValueAt(3).value_or("<empty>") << endl;
}

void testMultipleRemove() {
    LinkedList<string> list;
    list.InsertFirst("A");
    list.InsertFirst("B");
    list.InsertFirst("C");
    cout << "RemoveFirst: " << list.RemoveFirst().value_or("<empty>") << endl;
    cout << "The list should have length 2: " << list.Length() << endl;
    cout << "RemoveFirst: " << list.RemoveFirst().value_or("<empty>") << endl;
    cout << "The list should have length 1: " << list.Length() << endl;
    cout << "RemoveFirst: " << list.RemoveFirst().value_or("<empty>") << endl;
    cout << "The list should have length 0: " << list.Length() << endl;
    cout << "RemoveFirst (empty list): " << list.RemoveFirst().value_or("<empty>") << endl;
}

void testPrintList() {
    LinkedList<string> list;
    list.InsertFirst("1");
    list.InsertFirst("2");
    list.InsertFirst("3");
    cout << "Expected output from PrintList: [3,2,1]" << endl;
    list.PrintList();
}

void testInsertEmptyString() {
    LinkedList<string> list;
    list.InsertFirst("");
    cout << "The list should have length 1: " << list.Length() << endl;
    cout << "GetValueAt(0): " << list.GetValueAt(0).value_or("<empty>") << endl;
    cout << "RemoveFirst: " << list.RemoveFirst().value_or("<empty>") << endl;
    cout << "The list should have length 0: " << list.Length() << endl;
}

void testReinsertAfterRemoval() {
    LinkedList<string> list;
    list.InsertFirst("first");
    list.InsertFirst("second");
    cout << "RemoveFirst: " << list.RemoveFirst().value_or("<empty>") << endl;
    list.InsertFirst("third");
    cout << "The list should have length 2: " << list.Length() << endl;
    cout << "GetValueAt(0): " << list.GetValueAt(0).value_or("<empty>") << endl;
    cout << "GetValueAt(1): " << list.GetValueAt(1).value_or("<empty>") << endl;
}

void Test::testLinkedList() {
    testEmptyList();
    testSingleInsertRemove();
    testMultipleInsertGet();
    testMultipleRemove();
    testPrintList();
    testInsertEmptyString();
    testReinsertAfterRemoval();
}