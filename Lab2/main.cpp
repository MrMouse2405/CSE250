#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <iostream>
#include <optional>

#include "Lab2.h"
#include "QuickSort.h"
#include "MergeSort.h"
#include "Fib.h"

/**
 * @file Lab2.cpp
 * @brief CSE250 Lab2 - Flight Data Aggregation
 * @author OCdt Syed
 * @date 31/01/2025
 * @version 1.0
 *
 * This file contains the implementation for Lab2, which involves reading, sorting,
 * and displaying flight data from a CSV file.
 */

/**
 * @brief Reads input from a CSV file and populates a list with flight data.
 *
 * This function reads each line from the CSV file, parses it using the CSVParser,
 * and adds the parsed flight data to the provided list.
 *
 * @param data Reference to the list to populate with flight data.
 */
void readCSVFile(std::shared_ptr<FlightsList> data)
{
    // Open file, read data, close it.
    std::ifstream dataFile(FILE_NAME);
    if (!dataFile.is_open())
    {
        std::cout << "Failed to open file!" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string line;
    for (int i = 0; std::getline(dataFile, line); i++)
    {
        CSVParser parser(line);
        data->add(new FlightData{
            /* departure: */ parser.getWord(),
            /* arrival:   */ parser.getWord(),
            /* code:      */ parser.getWord(),
            /* cost:      */ parser.getDouble()});
    }

    dataFile.close();
}

/**
 * @brief Sorts the list of flights lexicographically by flight code using selection sort.
 *
 * This function sorts the provided list of flights in ascending order based on the flight code.
 *
 * @param data Reference to the list of FlightData pointers to be sorted.
 */
void sortFlights(std::shared_ptr<FlightsList> data)
{
    using std::size_t;
    const size_t len = data->getSize();
    for (size_t i = 0; i < len - 1; i++)
    {
        size_t min_idx = i;
        for (size_t j = i + 1; j < len; j++)
        {
            if (data->get(j)->code.compare(data->get(min_idx)->code) < 0)
            {
                min_idx = j;
            }
        }

        if (i != min_idx)
        {
            data->swap(i, min_idx);
        }
    }
}

/**
 * @brief Displays a preview of the flights in the list.
 *
 * This function displays the first and last 5 flights in the list.
 *
 * @param list Reference to the list of FlightData pointers to be previewed.
 */
void previewFlights(std::shared_ptr<FlightsList> list)
{
    std::cout << "The first 5 flights are: \n";
    for (size_t i = 0; i < 5; i++)
    {
        FlightData *data = list->get(i);
        std::cout << "Flight #" << data->code << " from " << data->departure << " to " << data->arrival << " costs " << data->cost << "$\n";
    }

    std::cout << "The last 5 flights are: \n";
    for (size_t i = list->getSize() - 5; i < list->getSize(); i++)
    {
        FlightData *data = list->get(i);
        std::cout << "Flight #" << data->code << " from " << data->departure << " to " << data->arrival << " costs " << data->cost << "$\n";
    }

    std::cout << std::endl;
}

/**
 * @brief Benchmarks a sorting function.
 *
 * This function benchmarks the provided sorting function by measuring the time taken
 * to sort the list and displaying the results.
 *
 * @tparam sort The sorting function to benchmark.
 * @param name The name of the sorting algorithm.
 */
template <SortFunction sort>
void bench(std::string name)
{
    using std::chrono::duration_cast;
    using std::chrono::milliseconds;
    using std::chrono::steady_clock;

    auto data = std::make_shared<FlightsList>();

    readCSVFile(data);

    std::cout << data->getSize() << " Flights Loaded.\n";
    previewFlights(data);

    auto start = steady_clock::now();
    sort(data);
    auto duration = duration_cast<milliseconds>(steady_clock::now() - start).count();
    std::cout << name << " SORTING took " << duration << "ms" << std::endl;
    previewFlights(data);

    start = steady_clock::now();
    sort(data);
    duration = duration_cast<milliseconds>(steady_clock::now() - start).count();
    std::cout << name << " RESORTING took " << duration << "ms" << std::endl;
    previewFlights(data);
}

/**
 * @brief Performs a binary search on a sorted list of flights to find a specific flight code.
 *
 * @param data A shared pointer to a FlightsList containing sorted flight data.
 * @param flightCode The flight code to search for.
 * @return std::optional<FlightData> The flight data if found, otherwise an empty optional.
 */
std::optional<FlightData> binarySearch(std::shared_ptr<FlightsList> data, const std::string &flightCode)
{
    std::size_t start = 0;
    std::size_t end = data->getSize() - 1;
    while (start <= end)
    {
        const std::size_t mid = start + (end - start) / 2;
        const int cmp = data->get(mid)->code.compare(flightCode);
        if (cmp == 0)
        {
            return {*(data->get(mid))};
        }
        else if (cmp < 0)
        {
            start = mid + 1;
        }
        else
        {
            end = mid - 1;
        }
    }

    return {};
}

/**
 * @brief Recursively generates and prints all binary strings of length n.
 *
 * This function generates all possible binary strings of a given length by
 * recursively appending '0' and '1' to the current string and printing it when
 * the string length reaches n.
 *
 * @param n The length of the binary strings to generate.
 * @param str The current binary string being built (default is an empty string).
 */
void listBinaryStrings(int n, std::string str = "")
{
    if (str.length() == n)
    {
        std::cout << str << std::endl;
        return;
    }
    listBinaryStrings(n, str + "0");
    listBinaryStrings(n, str + "1");
}

/**
 * @brief Main function for Lab2.
 *
 * This function benchmarks the selection sort and merge sort algorithms on flight data.
 *
 * @return int Returns 0 on successful execution.
 */
int main()
{
    std::cout << "-------------------------- Question 1 -------------------------- " << std::endl;
    bench<sortFlights>("SELECTION");

    std::cout << "-------------------------- Question 2 -------------------------- " << std::endl;
    bench<Lab2::mergeSort>("MERGE");

    std::cout << "-------------------------- Question 3 -------------------------- " << std::endl;
    bench<Lab2::quickSort>("QUICK");

    std::cout << "-------------------------- Question 4 -------------------------- " << std::endl;
    std::cout << "The second run of QuickSort is slower than first run because a sorted array"
                 " array is worst case scenario for quicksort. Therefore, it ends up taking O(n)"
                 " time. This is beecause the pivot selection consistently ends up in highly"
                 " unbalanced partitions, which makes the recursion tree very deep."
              << std::endl;

    std::cout << "-------------------------- Question 5 -------------------------- " << std::endl;
    {
        auto data = std::make_shared<FlightsList>();
        readCSVFile(data);
        Lab2::quickSort(data);
        for (std::string code : {"US0842", "FL0044", "GH2333"})
        {
            std::optional<FlightData> result = binarySearch(data, code);
            if (result.has_value())
            {
                std::cout << "The Flight " << result->code << " leaves " << result->departure << " for " << result->arrival << " and costs " << result->cost << "$" << std::endl;
            }
            else
            {
                std::cout << "The Flight " << code << " does not exist!" << std::endl;
            }
        }
    }

    std::cout << "-------------------------- Question 6 -------------------------- " << std::endl;
    std::cout << "Binary strings when n = 5 " << std::endl;
    listBinaryStrings(5);

    std::cout << "-------------------------- Question 7 -------------------------- " << std::endl;
    Lab2::runFib<Lab2::RecurF>(12, "recursive");
    Lab2::runFib<Lab2::IterF>(12, "iterative");
    std::cout << "The recursive version takes much more additions because due to redundant computations "
                 "of overlapping subproblems, leading to an exponential 2^n number of calls "
                 "(O(2^n) time complexity), whereas iterative approach avoids this ineffciency.\n"
                 "Note that my method uses less than 55 additions for iterative version "
                 "because of an implementation detail."
              << std::endl;

    return 0;
}