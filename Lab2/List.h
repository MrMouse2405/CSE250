#pragma once

#include <iostream>
#include <stdexcept>

namespace Lab2
{
    /**
     * @class List
     * @brief A dynamic array implementation that automatically resizes itself as elements are added.
     *
     * This class provides a dynamic array that grows in capacity as needed. It supports adding elements,
     * accessing elements via indexing, and provides methods to retrieve the size and capacity of the array.
     *
     * @tparam T The type of elements stored in the list.
     */
    template <typename T>
    class List
    {
    public:
        /**
         * @brief Constructs a new List object with an initial capacity.
         *
         * @param initialCapacity The initial capacity of the list (default is 4).
         */
        List(std::size_t initialCapacity = 4)
            : capacity(initialCapacity), size(0)
        {
            data = new T[capacity];
        }

        /**
         * @brief Destructor for the List object.
         *
         * Frees the dynamically allocated memory for the array.
         */
        ~List()
        {
            delete[] data;
        }

        /**
         * @brief Adds a new element to the end of the list.
         *
         * If the list is full, it automatically resizes to double its current capacity.
         *
         * @param value The value to be added to the list.
         */
        void add(const T value)
        {
            if (size == capacity)
            {
                resize(capacity * 2); // Double the capacity
            }
            data[size] = value;
            ++size;
        }

        /**
         * @brief Returns the value stored at the provided index.
         *
         * @param index The index of the element to access.
         * @return T The value at the specified index.
         * @throws std::out_of_range If the index is out of bounds.
         */
        T get(size_t index)
        {
            if (index >= size)
            {
                std::cerr << "get " << index << " > " << getSize() << std::endl;
                throw std::out_of_range("Index out of range");
            }
            return data[index];
        }

        /**
         * @brief Set the provided value at the provided index.
         *
         * @param index The index to place element at.
         * @param index The value to place at index.
         * @throws std::out_of_range If the index is out of bounds.
         */
        void set(size_t index, T value)
        {
            if (index >= size)
            {
                std::cerr << "set " << index << " > " << getSize() << std::endl;
                throw std::out_of_range("Index out of range");
            }
            this->data[index] = value;
        }

        /**
         * @brief Returns the number of elements in the list.
         *
         * @return std::size_t The number of elements in the list.
         */
        std::size_t getSize() const
        {
            return size;
        }

        /**
         * @brief Returns the current capacity of the list.
         *
         * The capacity is the total number of elements the list can hold without resizing.
         *
         * @return std::size_t The capacity of the list.
         */
        std::size_t getCapacity() const
        {
            return capacity;
        }

        /**
         * @brief Swaps two elements in the list.
         *
         * @param index1 The index of the first element to swap.
         * @param index2 The index of the second element to swap.
         */
        void swap(std::size_t index1, std::size_t index2)
        {
            T temp = this->data[index1];
            this->data[index1] = this->data[index2];
            this->data[index2] = temp;
        }

    private:
        T *data;              ///< Pointer to the dynamically allocated array.
        std::size_t capacity; ///< Current capacity of the array.
        std::size_t size;     ///< Number of elements currently in the array.

        /**
         * @brief Resizes the array to a new capacity.
         *
         * This function allocates a new array with the specified capacity, copies the existing elements
         * to the new array, and deallocates the old array.
         *
         * @param newCapacity The new capacity for the array.
         */
        void resize(std::size_t newCapacity)
        {
            T *newData = new T[newCapacity];
            std::copy(data, data + capacity, newData);
            delete[] data;
            data = newData;
            capacity = newCapacity;
        }
    };
}