/******************************************************************************
 * TestQueue.cpp
 *
 *  Created on: Feb 07 2025
 *      Author: OCdt Syed
 *
 *  Implementation details:
 *      This file tests the Queue class using various test cases.
 *
 ******************************************************************************/

#include <iostream>
#include <cassert>
#include "Test.h"
#include "Queue.h"

using namespace std;

/**
 * Tests an empty queue.
 * Verifies that the queue is initially empty, not full, and prints as "[]".
 */
void testEmptyQueue() {
    const Queue q(5);
    assert(q.IsEmpty() == true);
    assert(q.IsFull() == false);
    Test::testOutput([&]() { q.PrintQueue(); }, "[]\n");
}

/**
 * Tests enqueuing elements and printing the queue.
 * Enqueues several elements and verifies that the printed order is correct.
 */
void testEnqueueAndPrint() {
    Queue q(5);
    assert(q.Enqueue(10) == true);
    assert(q.Enqueue(20) == true);
    assert(q.Enqueue(30) == true);
    Test::testOutput([&]() { q.PrintQueue(); }, "[10,20,30]\n");
    assert(q.IsEmpty() == false);
    assert(q.IsFull() == false);
}

/**
 * Tests dequeuing elements.
 * Enqueues several elements, then dequeues them and verifies that the correct elements are removed.
 */
void testDequeue() {
    Queue q(5);
    q.Enqueue(10);
    q.Enqueue(20);
    q.Enqueue(30);

    int value = 0;
    assert(q.Dequeue(value) == true);
    assert(value == 10);
    Test::testOutput([&]() { q.PrintQueue(); }, "[20,30]\n");

    assert(q.Dequeue(value) == true);
    assert(value == 20);
    assert(q.Dequeue(value) == true);
    assert(value == 30);

    assert(q.IsEmpty() == true);
    assert(q.Dequeue(value) == false);
    Test::testOutput([&]() { q.PrintQueue(); }, "[]\n");
}

/**
 * Tests the scenario when the queue becomes full.
 * Enqueues elements until the queue is full and verifies that further enqueues fail.
 */
void testFullQueue() {
    Queue q(3);
    assert(q.Enqueue(1) == true);
    assert(q.Enqueue(2) == true);
    assert(q.Enqueue(3) == true);
    assert(q.IsFull() == true);
    assert(q.Enqueue(4) == false);
    Test::testOutput([&]() { q.PrintQueue(); }, "[1,2,3]\n");
}

/**
 * Tests the circular behavior of the queue.
 * Enqueues and dequeues elements to verify that the circular buffer wraps around correctly.
 */
void testCircularBehavior() {
    Queue q(3);
    assert(q.Enqueue(1) == true);
    assert(q.Enqueue(2) == true);
    assert(q.Enqueue(3) == true);

    int value = 0;
    assert(q.Dequeue(value) == true);
    assert(value == 1);
    assert(q.Enqueue(4) == true);
    Test::testOutput([&]() { q.PrintQueue(); }, "[2,3,4]\n");

    assert(q.Dequeue(value) == true); // should be 2
    assert(value == 2);
    assert(q.Dequeue(value) == true); // should be 3
    assert(value == 3);
    assert(q.Dequeue(value) == true); // should be 4
    assert(value == 4);
    assert(q.Dequeue(value) == false);
}

/**
 * Runs all Queue tests.
 * Calls each individual test function and prints a message upon successful completion.
 */
void Test::testQueue() {
    testEmptyQueue();
    cout << "testEmptyQueue passed." << endl;

    testEnqueueAndPrint();
    cout << "testEnqueueAndPrint passed." << endl;

    testDequeue();
    cout << "testDequeue passed." << endl;

    testFullQueue();
    cout << "testFullQueue passed." << endl;

    testCircularBehavior();
    cout << "testCircularBehavior passed." << endl;

    cout << "All tests passed successfully." << endl;
}
