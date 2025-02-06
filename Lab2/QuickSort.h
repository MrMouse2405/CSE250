#pragma once
#include "Lab2.h"

namespace Lab2
{
    /**
     * @brief Partitions the list for Quick Sort.
     *
     * This function partitions the list around a pivot element such that all elements
     * less than the pivot are on the left, and all elements greater than the pivot are on the right.
     *
     * @param list The list to partition.
     * @param low The starting index of the sublist.
     * @param high The ending index of the sublist.
     * @return std::size_t The index of the pivot element after partitioning.
     */
    std::size_t partition(std::shared_ptr<FlightsList> list, std::size_t low, std::size_t high)
    {
        std::string pivot = list->get(high)->code;
        std::size_t i = low;

        for (std::size_t j = low; j < high; j++)
        {

            if (list->get(j)->code.compare(pivot) <= 0)
            {
                list->swap(i, j);
                i++;
            }
        }
        list->swap(i, high);
        return i;
    }

    /**
     * @brief Recursively sorts a sublist using the Quick Sort algorithm.
     *
     * This function sorts the sublist from index `low` to `high` using the Quick Sort algorithm.
     *
     * @param list The list to sort.
     * @param low The starting index of the sublist.
     * @param high The ending index of the sublist.
     */
    void quickSort(std::shared_ptr<FlightsList> list, std::size_t low, std::size_t high)
    {
        if (low < high)
        {
            std::size_t pivotIndex = partition(list, low, high);

            if (pivotIndex > 0) // Avoid underflow
                quickSort(list, low, pivotIndex - 1);
            quickSort(list, pivotIndex + 1, high);
        }
    }

    /**
     * @brief Sorts the list of flights lexicographically by flight code using Quick Sort.
     *
     * This function sorts the provided list of flights in ascending order based on the flight code.
     *
     * @param data Reference to the list of FlightData pointers to be sorted.
     */
    void quickSort(std::shared_ptr<FlightsList> data)
    {
        quickSort(data, 0, data->getSize() - 1);
    }
}