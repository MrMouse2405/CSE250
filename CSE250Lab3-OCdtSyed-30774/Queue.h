/******************************************************************************
 * Queue.h
 *
 *  Created on: Feb 07 2025
 *      Author: OCdt Syed
 *
 *  Implementation details:
 *      A fixed-size queue of integers using a circular buffer.
 *
 ******************************************************************************/

#pragma once
#include <memory>
#include <iostream>

/**
 * A fixed-size queue of integers implemented with a circular buffer.
 */
class Queue {
private:
    /** Maximum number of elements in the queue. */
    const std::size_t m_MaxSize;
    /** The circular buffer holding the queue elements. */
    std::unique_ptr<int[]> m_Data;
    /** Index of the front element in the queue. */
    std::size_t m_First;
    /** Current number of elements in the queue. */
    std::size_t m_Size;

public:
    /**
     * Constructs a queue with the given maximum size.
     * @param new_max_size The maximum number of elements.
     */
    explicit Queue(std::size_t new_max_size)
        : m_MaxSize(new_max_size),
          m_Data(new int[new_max_size]),
          m_First(0),
          m_Size(0) {
    }

    /**
     * Destructor
     */
    ~Queue() = default;

    /**
     * Returns true if the queue is empty, false otherwise.
     * @return true if empty; false otherwise.
     */
    [[nodiscard]] bool IsEmpty() const {
        return m_Size == 0;
    }

    /**
     * Returns true if the queue is full, false otherwise.
     * @return true if full; false otherwise.
     */
    [[nodiscard]] bool IsFull() const {
        return m_Size == m_MaxSize;
    }

    /**
     * Prints the contents of the queue in a single line (e.g., [3,19,2,36]).
     */
    void PrintQueue() const {
        if (m_Size == 0) {
            std::cout << "[]" << std::endl;
            return;
        }
        std::cout << "[";
        for (std::size_t i = 0; i < m_Size - 1; i++) {
            std::cout << m_Data[(m_First + i) % m_MaxSize] << ",";
        }
        std::cout << m_Data[(m_First + m_Size - 1) % m_MaxSize] << "]" << std::endl;
    }

    /**
     * Enqueues a new element at the end of the queue.
     * @param new_value The integer value to enqueue.
     * @return true if the element was added; false if the queue is full.
     */
    bool Enqueue(const int new_value) {
        if (m_Size == m_MaxSize)
            return false;
        m_Data[(m_First + m_Size) % m_MaxSize] = new_value;
        ++m_Size;
        return true;
    }

    /**
     * Dequeues the front element of the queue.
     * @param old_value A reference to store the removed element.
     * @return true if successful; false if the queue is empty.
     */
    bool Dequeue(int &old_value) {
        if (m_Size == 0)
            return false;
        old_value = m_Data[m_First];
        m_First = (m_First + 1) % m_MaxSize;
        --m_Size;
        return true;
    }
};
