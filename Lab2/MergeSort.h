#pragma once
#include "Lab2.h"

namespace Lab2
{
    /**
     * @brief Merges two sublists in sorted order.
     *
     * This function merges two sorted sublists into a single sorted list.
     *
     * @param list The list containing the sublists to merge.
     * @param left The starting index of the first sublist.
     * @param middle The ending index of the first sublist and starting index of the second sublist.
     * @param right The ending index of the second sublist.
     */
    void merge(std::shared_ptr<FlightsList> list, std::size_t left, std::size_t middle, std::size_t right)
    {
        std::size_t l1 = middle - left + 1;
        std::size_t l2 = right - middle;

        FlightsList leftList(l1);
        FlightsList rightList(l2);
        for (std::size_t i = 0; i < l1; i++)
        {
            leftList.add(list->get(left + i));
        }
        for (std::size_t i = 0; i < l2; i++)
        {
            rightList.add(list->get(middle + 1 + i));
        }

        std::size_t i = 0, j = 0, k = left;
        while (i < l1 && j < l2)
        {
            if (leftList.get(i)->code.compare(rightList.get(j)->code) <= 0)
            {
                list->set(k++, leftList.get(i++));
            }
            else
            {
                list->set(k++, rightList.get(j++));
            }
        }

        while (i < l1)
        {
            list->set(k++, leftList.get(i++));
        }

        while (j < l2)
        {
            list->set(k++, rightList.get(j++));
        }
    }

    /**
     * @brief Recursively sorts a sublist using the merge sort algorithm.
     *
     * This function sorts the sublist from index `left` to `right` using the merge sort algorithm.
     *
     * @param list The list to sort.
     * @param left The starting index of the sublist.
     * @param right The ending index of the sublist.
     */
    void mergeSort(std::shared_ptr<FlightsList> list, std::size_t left, std::size_t right)
    {
        if (left >= right)
            return;

        std::size_t middle = left + (right - left) / 2;
        mergeSort(list, left, middle);
        mergeSort(list, middle + 1, right);
        merge(list, left, middle, right);
    }

    /**
     * @brief Sorts the list of flights lexicographically by flight code using merge sort.
     *
     * This function sorts the provided list of flights in ascending order based on the flight code.
     *
     * @param data Reference to the list of FlightData pointers to be sorted.
     */
    void mergeSort(std::shared_ptr<FlightsList> data)
    {
        mergeSort(data, 0, data->getSize() - 1);
    }
}