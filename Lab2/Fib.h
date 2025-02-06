#pragma once

#include "Lab2.h"
namespace Lab2
{
    /**
     * @brief Recursively computes the Fibonacci sequence and counts additions.
     *
     * @param n The Fibonacci index to compute.
     * @param counter A pointer to count the number of additions performed.
     * @return int The Fibonacci number at index n.
     */
    int RecurF(std::size_t n, std::size_t *counter)
    {
        if (n == 0)
        {
            return 0;
        }
        if (n == 1)
        {
            return 1;
        }

        *counter += 1;
        return RecurF(n - 1, counter) + RecurF(n - 2, counter);
    }

    /**
     * @brief Iteratively computes the Fibonacci sequence and counts additions.
     *
     * @param n The Fibonacci index to compute.
     * @param counter A pointer to count the number of additions performed.
     * @return int The Fibonacci number at index n.
     */
    int IterF(std::size_t n, std::size_t *counter)
    {
        if (n == 0)
        {
            return 0;
        }
        if (n < 3)
        {
            return 1;
        }
        int n_1 = 1;
        int n_2 = 1;
        int x = 0;
        for (int i = 3; i <= n; i++)
        {
            *counter += 1;
            x = n_1 + n_2;
            n_2 = n_1;
            n_1 = x;
        }
        return x;
    }

    /**
     * @brief Runs a specified Fibonacci function and prints the sequence along with the number of additions used.
     *
     * @tparam fib A function pointer to either the recursive or iterative Fibonacci implementation.
     * @param n The number of Fibonacci numbers to compute.
     * @param method A string describing the method used (e.g., "Recursively" or "Iteratively").
     */
    template <int (*fib)(std::size_t, std::size_t *)>
    void runFib(int n, std::string method)
    {
        std::cout << "The first " << n << " F numbers computed " << method << " are ";

        int result;
        std::size_t counter = 0;
        for (size_t i = 0; i < n; i++)
        {
            result = fib(i, &counter);
            std::cout << result << ",";
        }
        std::cout << " and it used " << counter << " additions" << std::endl;
    }

}