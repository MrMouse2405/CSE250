/******************************************************************************
 * QueueTest.cpp
 *
 * This file tests the Queue class.
 *
 * To compile (for example, with g++):
 *    g++ -std=c++11 -o QueueTest QueueTest.cpp Queue.cpp
 *
 * Then run:
 *    ./QueueTest
 *
 ******************************************************************************/

#include <cassert>
#include <sstream>
#include <iostream>
#include "Queue.h"

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

void testEmptyQueue()
{
    Queue q(5);
    // Initially, the queue should be empty and not full.
    assert(q.IsEmpty() == true);
    assert(q.IsFull() == false);
    testOutput([&]()
               { q.PrintQueue(); }, "[]\n");
}

void testEnqueueAndPrint()
{
    Queue q(5);
    // Enqueue a few elements.
    assert(q.Enqueue(10) == true);
    assert(q.Enqueue(20) == true);
    assert(q.Enqueue(30) == true);
    // Expected order: [10,20,30]
    testOutput([&]()
               { q.PrintQueue(); }, "[10,20,30]\n");
    // After enqueuing, the queue is not empty.
    assert(q.IsEmpty() == false);
    // And it is not full.
    assert(q.IsFull() == false);
}

void testDequeue()
{
    Queue q(5);
    // Enqueue some elements.
    q.Enqueue(10);
    q.Enqueue(20);
    q.Enqueue(30);

    int value = 0;
    // First Dequeue: should remove 10.
    assert(q.Dequeue(value) == true);
    assert(value == 10);
    testOutput([&]()
               { q.PrintQueue(); }, "[20,30]\n");

    // Next Dequeues.
    assert(q.Dequeue(value) == true);
    assert(value == 20);
    assert(q.Dequeue(value) == true);
    assert(value == 30);

    // Queue should now be empty.
    assert(q.IsEmpty() == true);
    // Attempting to dequeue from an empty queue should fail.
    assert(q.Dequeue(value) == false);
    testOutput([&]()
               { q.PrintQueue(); }, "[]\n");
}

void testFullQueue()
{
    Queue q(3);
    // Fill the queue.
    assert(q.Enqueue(1) == true);
    assert(q.Enqueue(2) == true);
    assert(q.Enqueue(3) == true);
    // Now, the queue should be full.
    assert(q.IsFull() == true);
    // Enqueue should now fail.
    assert(q.Enqueue(4) == false);
    testOutput([&]()
               { q.PrintQueue(); }, "[1,2,3]\n");
}

void testCircularBehavior()
{
    Queue q(3);
    // Enqueue three elements.
    assert(q.Enqueue(1) == true);
    assert(q.Enqueue(2) == true);
    assert(q.Enqueue(3) == true);

    int value = 0;
    // Dequeue one element (removes 1).
    assert(q.Dequeue(value) == true);
    assert(value == 1);
    // Enqueue another element (should wrap around to the freed slot).
    assert(q.Enqueue(4) == true);
    // Expected order now: [2,3,4]
    testOutput([&]()
               { q.PrintQueue(); }, "[2,3,4]\n");

    // Dequeue remaining elements to verify order.
    assert(q.Dequeue(value) == true); // should be 2
    assert(value == 2);
    assert(q.Dequeue(value) == true); // should be 3
    assert(value == 3);
    assert(q.Dequeue(value) == true); // should be 4
    assert(value == 4);
    // Now the queue is empty.
    assert(q.Dequeue(value) == false);
}

int main()
{
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
    return 0;
}
