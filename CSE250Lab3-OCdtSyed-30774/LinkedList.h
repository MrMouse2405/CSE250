/****************************************************************************\
 * LinkedList.h
 *
 *  Created on: Feb, 06, 2025
 *      Author: OCdt Syed
 *
 *  Implementation details: Generic doubly-linked list.
 *
 \***************************************************************************/

#pragma once
#include <optional>
#include <iostream>

/**
 * Generic node for a doubly-linked list.
 */
template<typename T>
struct Node {
    /** The stored value. */
    T value;
    /** Pointer to the next node, if any. */
    std::optional<Node<T> *> next;
    /** Pointer to the previous node, if any. */
    std::optional<Node<T> *> prev;

    /**
     * Constructs a node with the given value and pointers.
     * @param value The stored value.
     * @param next Pointer to the next node.
     * @param prev Pointer to the previous node.
     */
    Node(T value, std::optional<Node<T> *> next, std::optional<Node<T> *> prev)
        : value(value), next(next), prev(prev) {
    }
};

/**
 * Generic doubly-linked list.
 */
template<typename T>
class LinkedList {
private:
    /** Pointer to the first node of the list (if any). */
    std::optional<Node<T> *> m_First = std::nullopt;
    /** Number of nodes in the list. */
    std::size_t length = 0;

public:
    /**
     * Constructs an empty list.
     */
    LinkedList() : m_First(std::nullopt), length(0) {
    }

    /**
     * Destructor. Frees all nodes in the list.
     */
    ~LinkedList() {
        while (length > 0) {
            RemoveFirst();
        }
    }

    /**
     * Returns the length of the list in O(1).
     * @return The number of nodes in the list.
     */
    [[nodiscard]] std::size_t Length() const {
        return length;
    }

    /**
     * Prints all elements of the list on a single line separated by commas.
     * Example output: [3,19,2,36]
     */
    void PrintList() const {
        std::cout << "[";
        Node<T> *current = (m_First.has_value() ? m_First.value() : nullptr);
        bool firstElement = true;
        while (current) {
            if (!firstElement) {
                std::cout << ",";
            }
            std::cout << current->value;
            firstElement = false;
            if (current->next.has_value())
                current = current->next.value();
            else
                current = nullptr;
        }
        std::cout << "]\n";
    }

    /**
     * Inserts a new value at the beginning of the list in O(1).
     * @param new_value The value to insert.
     */
    void InsertFirst(const T &new_value) {
        auto *newNode = new Node<T>(new_value, m_First, std::nullopt);
        if (m_First.has_value()) {
            m_First.value()->prev = newNode;
        }
        m_First = newNode;
        ++length;
    }

    /**
     * Removes and returns the first element of the list in O(1).
     * @return An optional containing the removed value, or std::nullopt if empty.
     */
    std::optional<T> RemoveFirst() {
        if (!m_First.has_value()) {
            return std::nullopt;
        }
        Node<T> *nodeToRemove = m_First.value();
        T retVal = nodeToRemove->value;
        if (nodeToRemove->next.has_value()) {
            m_First = nodeToRemove->next.value();
            m_First.value()->prev = std::nullopt;
        } else {
            m_First = std::nullopt;
        }
        delete nodeToRemove;
        --length;
        return retVal;
    }

    /**
     * Returns the value at the given index (0-based) in O(n).
     * @param index The index of the element.
     * @return An optional containing the value, or std::nullopt if index is out of bounds.
     */
    std::optional<T> GetValueAt(const std::size_t index) const {
        if (index >= length) {
            return std::nullopt;
        }
        Node<T> *current = m_First.value();
        for (std::size_t i = 0; i < index; ++i) {
            if (!current->next.has_value())
                return std::nullopt;
            current = current->next.value();
        }
        return current->value;
    }
};
