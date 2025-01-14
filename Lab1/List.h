#pragma once

#include <iostream>
#include <stdexcept>

namespace Lab1
{
    /**
     *
     * List
     *
     * Array implementation that automatically resizes itself
     * as number of elements grow inside the array.
     *
     */

    template <typename T>
    class List
    {
    public:
        /**
         *
         * Constructor
         *
         * @param initialCapacity, initial size of array
         *
         */
        List(std::size_t initialCapacity = 4)
            : capacity(initialCapacity), size(0)
        {
            data = new T[capacity];
        }

        /**
         *
         * Destructor
         *
         */
        ~List()
        {
            delete[] data;
        }

        /**
         *
         * add()
         *
         * Inserts a new value at the end of array.
         *
         * @param value, value to insert.
         *
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
         *
         * operator[]
         *
         * Implementation for indexing / index & assigning a value
         * to the array. Works similar to regular array indexing.
         *
         * @param index, index of the value
         * @returns T&, reference to the indexed value
         *
         */
        T &operator[](size_t index)
        {
            if (index >= size)
            {
                throw std::out_of_range("Index out of range");
            }
            return data[index];
        }

        /**
         *
         * const operator[]
         *
         * Same as operator[]. but operation is constant
         *
         * @param index const, index of the value
         * @returns T& const, reference to the indexed value
         */
        const T &operator[](size_t index) const
        {
            if (index >= size)
            {
                throw std::out_of_range("Index out of range");
            }
            return data[index];
        }

        /**
         *
         * getSize()
         *
         * Returns the size of the array.
         *
         * @returns std::size_t, size of array
         *
         */
        std::size_t getSize() const
        {
            return size;
        }

        /**
         *
         * getCapacity()
         *
         * Returns the capacity of the array.
         *
         * Note: size is # of elements stored in array,
         *       capacity is memory allocated for array
         *
         *       size <= capacity
         *
         * @returns std::size_t, capacity of the array.
         *
         */
        std::size_t getCapacity() const
        {
            return capacity;
        }

    private:
        T *data;              // Pointer to the array
        std::size_t capacity; // Current capacity of the array
        std::size_t size;     // Number of elements in the array

        /**
         *
         * resize()
         *
         * Resizes the array.
         *
         * @param newCapacity, capacity to resize to.
         *
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