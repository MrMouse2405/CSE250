/******************************************************************************
 * Stack.h
 *
 *  Created on: Feb 07 2025
 *      Author: OCdt Syed
 *
 *  Implementation details:
 *      A generic stack implemented on top of a LinkedList<T>.
 *
 ******************************************************************************/

#pragma once
#include "LinkedList.h"
#include <optional>
#include <iostream>

/**
 * A generic stack class implemented using a LinkedList<T>.
 */
template <typename T>
class Stack final {
private:
    /** The underlying linked list that holds the stack elements. */
    mutable LinkedList<T> m_List;

public:
    /**
     * Constructs an empty stack.
     */
    Stack() : m_List() { }

    /**
     * Destructor.
     */
    ~Stack() = default;

    /**
     * Returns whether the stack is empty in O(1).
     * @return true if the stack is empty; false otherwise.
     */
    bool IsEmpty() {
        return m_List.Length() == 0;
    }

    /**
     * Prints the stack from top to bottom (one element per line).
     */
    void PrintStack() {
        const std::size_t len = m_List.Length();
        for (std::size_t i = 0; i < len; ++i) {
            auto val = m_List.GetValueAt(i);
            /** Prints the value (if available) or a default-constructed T. */
            std::cout << (val.has_value() ? val.value() : T()) << "\n";
        }
    }

    /**
     * Pushes a new value onto the stack in O(1).
     * @param new_value The value to push onto the stack.
     */
    void Push(const T &new_value) {
        m_List.InsertFirst(new_value);
    }

    /**
     * Pops the top value off the stack in O(1).
     * @return An optional containing the popped value or std::nullopt if empty.
     */
    std::optional<T> Pop() {
        return m_List.RemoveFirst();
    }

    /**
     * Returns the top value of the stack in O(1) without removing it.
     * @return An optional containing the top value or std::nullopt if empty.
     */
    std::optional<T> Top() {
        return m_List.GetValueAt(0);
    }
};
