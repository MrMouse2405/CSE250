/******************************************************************************
 * TestQueue.cpp
 *
 *  Created on: Feb 07 2025
 *      Author: OCdt Syed
 *
 *  Implementation details:
 *      This file tests the Queue using various test cases.
 *
 ******************************************************************************/

#include <iostream>
#include "Test.h"
#include "Queue.h"

using namespace std;

void testEmptyQueue() {
    const Queue q(5);
    cout << "Queue should be empty: " << (q.IsEmpty() ? "true" : "false") << endl;
    cout << "Queue should not be full: " << (q.IsFull() ? "true" : "false") << endl;
    cout << "Expected output from PrintQueue: []" << endl;
    q.PrintQueue();
}

void testEnqueueAndPrint() {
    Queue q(5);
    cout << "Enqueuing 10: " << (q.Enqueue(10) ? "success" : "fail") << endl;
    cout << "Enqueuing 20: " << (q.Enqueue(20) ? "success" : "fail") << endl;
    cout << "Enqueuing 30: " << (q.Enqueue(30) ? "success" : "fail") << endl;
    cout << "Expected output from PrintQueue: [10,20,30]" << endl;
    q.PrintQueue();
    cout << "Queue should not be empty: " << (q.IsEmpty() ? "true" : "false") << endl;
    cout << "Queue should not be full: " << (q.IsFull() ? "true" : "false") << endl;
}

void testDequeue() {
    Queue q(5);
    q.Enqueue(10);
    q.Enqueue(20);
    q.Enqueue(30);
    int value = 0;
    cout << "Dequeuing: " << (q.Dequeue(value) ? "success" : "fail") << " Value: " << value << endl;
    cout << "Expected output from PrintQueue: [20,30]" << endl;
    q.PrintQueue();
    cout << "Dequeuing: " << (q.Dequeue(value) ? "success" : "fail") << " Value: " << value << endl;
    cout << "Dequeuing: " << (q.Dequeue(value) ? "success" : "fail") << " Value: " << value << endl;
    cout << "Queue should be empty: " << (q.IsEmpty() ? "true" : "false") << endl;
    cout << "Dequeuing from empty queue: " << (q.Dequeue(value) ? "success" : "fail") << endl;
}

void testFullQueue() {
    Queue q(3);
    q.Enqueue(1);
    q.Enqueue(2);
    q.Enqueue(3);
    cout << "Queue should be full: " << (q.IsFull() ? "true" : "false") << endl;
    cout << "Enqueuing 4 (should fail): " << (q.Enqueue(4) ? "success" : "fail") << endl;
    cout << "Expected output from PrintQueue: [1,2,3]" << endl;
    q.PrintQueue();
}

void testCircularBehavior() {
    Queue q(3);
    q.Enqueue(1);
    q.Enqueue(2);
    q.Enqueue(3);
    int value = 0;
    q.Dequeue(value);
    cout << "Dequeued value: " << value << endl;
    q.Enqueue(4);
    cout << "Expected output from PrintQueue: [2,3,4]" << endl;
    q.PrintQueue();
    q.Dequeue(value);
    cout << "Dequeued value: " << value << endl;
    q.Dequeue(value);
    cout << "Dequeued value: " << value << endl;
    q.Dequeue(value);
    cout << "Dequeued value: " << value << endl;
    cout << "Dequeuing from empty queue: " << (q.Dequeue(value) ? "success" : "fail") << endl;
}

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
