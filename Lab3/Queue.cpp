/******************************************************************************
 * Queue.cpp
 *
 *  Created on:
 *      Author: YOUR NAME
 *
 *  Implementation details:
 *      A circular queue implementation using a fixed-size array allocated via
 *      a const unique_ptr. The queue tracks the index of its first element (m_First)
 *      and the current number of elements (size). When adding or removing, indices
 *      wrap around using modulo arithmetic.
 *
 ******************************************************************************/
#include <iostream>
#include <cassert>
#include <sstream>

#include "Queue.h"

using namespace std;

Queue::Queue(size_t new_max_size)
    : m_Data(new int[new_max_size]), // Initialize the unique_ptr with a new array.
      m_MaxSize(new_max_size),
      m_First(0),
      size(0)
{
}

Queue::~Queue()
{
    // No need to delete m_Data manually because unique_ptr handles it.
}

bool Queue::IsEmpty()
{
    return size == 0;
}

bool Queue::IsFull()
{
    return size == m_MaxSize;
}

void Queue::PrintQueue()
{
    if (size == 0)
    {
        cout << "[]" << endl;
        return;
    }

    cout << "[";
    for (size_t idx = 0; idx < size - 1; idx++)
    {
        cout << m_Data[(m_First + idx) % m_MaxSize] << ",";
    }
    cout << m_Data[(m_First + size - 1) % m_MaxSize] << "]" << endl;
}

bool Queue::Enqueue(int new_value)
{
    if (size == m_MaxSize)
    {
        return false;
    }

    m_Data[(m_First + size) % m_MaxSize] = new_value;
    size++;
    return true;
}

bool Queue::Dequeue(int &old_value)
{
    if (size == 0)
    {
        return false;
    }

    // Retrieve the front element.
    old_value = m_Data[m_First];
    // Advance m_First (wrapping around if necessary).
    m_First = (m_First + 1) % m_MaxSize;
    size--;
    return true;
}
