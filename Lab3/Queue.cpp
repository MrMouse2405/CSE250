/****************************************************************************\
 * Queue.cpp
 *
 *  Created on:
 *      Author: YOUR NAME
 *
 *
 *  Implementation details: ?
 *  \\TODO
 *  You can add your implementation details here or in the header,
 *  or with the appropriate variable's or function's comments.
 *
 \***************************************************************************/

#include <iostream>
#include "Queue.h"

using namespace std;

Queue::Queue(size_t new_max_size) : m_MaxSize(new_max_size), m_Data(new int[new_max_size])
{
    m_First = 0;
    size = 0;
}

/** Deletes the queue and free up its memory. */
Queue::~Queue()
{
}

/** Indicates whether of not the queue is empty in O(1), true if empty, false if not. */
bool Queue::IsEmpty()
{
    return size < m_MaxSize;
}

/** Indicates whether of not the queue is full in O(1), true if full, false if not. */
bool Queue::IsFull()
{
    return size == m_MaxSize;
}

/** Prints the content of the queue on a single line, separated by comma, eg: [3, 19, 2, 36]. */
void Queue::PrintQueue()
{

    if (size == 0)
    {
        cout << "[]" << endl;
    }

    cout << "[";
    for (size_t idx = 0; idx < size - 1; idx++)
    {
        cout << m_Data[idx];
        cout << ",";
    }
    cout << m_Data[size - 1];
    cout << "]" << endl;
}

/** Inserts an element at the end of the queue, returns true if succeed, and false if the queue is already full. */
bool Queue::Enqueue(int new_value)
{
    if (size == m_MaxSize)
    {
        return false;
    }

    m_Data[(m_First + size) % m_MaxSize] = new_value;
    size += 1;
    return true;
}
/** Removes the element at the front of the queue and returns the element in the argument,
 * returns true if succeed, and false if the queue is already empty.  */
bool Queue::Dequeue(int &old_value)
{

    if (size == 0)
    {
        return false;
    }

    old_value = m_Data[(m_First + size) % m_MaxSize];

    m_First = (m_First + 1) % m_MaxSize;

    return true;
}
