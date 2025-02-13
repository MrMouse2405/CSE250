/******************************************************************************
* Test.h
 *
 *  Created on: Feb 13 2025
 *      Author: OCdt Syed
 *
 *  Implementation details:
 *      Provides functions for testing various components such as Stack,
 *      LinkedList, Queue, and PostFixCalculator.
 *
 ******************************************************************************/

#pragma once
#include <string>
#include <sstream>
#include <iostream>
#include <cassert>

namespace Test {
    /**
     * Template function that captures the output of a lambda and asserts that it matches the expected string.
     * @param lambda The lambda function that produces output.
     * @param expected The expected output string.
     */
    template<typename F>
    inline void testOutput(F &&lambda, const std::string &expected) {
        using namespace std;
        std::ostringstream oss; /** Use a non-const ostringstream so output can be captured. */
        std::streambuf *oldBuf = std::cout.rdbuf();
        std::cout.rdbuf(oss.rdbuf());
        lambda();
        std::cout.rdbuf(oldBuf);
        assert(oss.str() == expected);
    }

    /** Tests the Stack component. */
    void testStack();

    /** Tests the LinkedList component. */
    void testLinkedList();

    /** Tests the Queue component. */
    void testQueue();

    /** Tests the PostFixCalculator component. */
    void testPostFixCalculator();
}
