#include <iostream>
#include <stdexcept>

namespace Lab1
{
    template <typename T>
    class List
    {
    public:
        List(size_t initialCapacity = 4)
            : capacity(initialCapacity), size(0)
        {
            data = new T[capacity];
        }

        ~List()
        {
            delete[] data;
        }

        void add(const T value)
        {
            if (size == capacity)
            {
                resize(capacity * 2); // Double the capacity
            }
            data[size] = value;
            ++size;
        }

        T &operator[](size_t index)
        {
            if (index >= size)
            {
                throw std::out_of_range("Index out of range");
            }
            return data[index];
        }

        const T &operator[](size_t index) const
        {
            if (index >= size)
            {
                throw std::out_of_range("Index out of range");
            }
            return data[index];
        }

        std::size_t getSize() const
        {
            return size;
        }

        std::size_t getCapacity() const
        {
            return capacity;
        }

    private:
        T *data;              // Pointer to the array
        std::size_t capacity; // Current capacity of the array
        std::size_t size;     // Number of elements in the array

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