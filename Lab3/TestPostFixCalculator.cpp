/******************************************************************************
 * PostFixCalculatorTest.cpp
 *
 *  Created on: Feb 13 2025
 *      Author: OCdt Syed
 *
 *  Implementation details:
 *      This file tests the PostFixCalculator function using various test cases.
 *
 ******************************************************************************/

#include <cassert>
#include <iostream>
#include "PostFixCalculator.h"
#include "Test.h"

using namespace std;

/**
 * Tests addition in a postfix expression.
 * The expression "4,5,+" should yield 9.
 */
void testAddition() {
    assert(PostFixCalculator("4,5,+") == 9);
}

/**
 * Tests multiplication in a postfix expression.
 * The expression "3,9,*" should yield 27.
 */
void testMultiplication() {
    assert(PostFixCalculator("3,9,*") == 27);
}

/**
 * Tests subtraction with grouping in a postfix expression.
 * The expression "2,5,3,+,-" should yield -6 (because 5+3=8 then 2-8=-6).
 */
void testSubtractionWithGrouping() {
    assert(PostFixCalculator("2,5,3,+,-") == -6);
}

/**
 * Tests a complex postfix expression.
 * The expression "1,5,+,8,4,1,-,-,*" should yield 30.
 * Explanation:
 *  1,5,+  -> 6
 *  4,1,-  -> 3
 *  8,3,-  -> 5
 *  6,5,*  -> 30
 */
void testComplexExpression() {
    assert(PostFixCalculator("1,5,+,8,4,1,-,-,*") == 30);
}

/**
 * Tests division in a postfix expression.
 * The expression "10,2,/" should yield 5.
 */
void testDivision() {
    assert(PostFixCalculator("10,2,/") == 5);
}

/**
 * Tests division by zero in a postfix expression.
 * The expression "10,0,/" should throw a runtime_error.
 */
void testDivisionByZero() {
    bool caught = false;
    try {
        PostFixCalculator("10,0,/");
    } catch (const std::runtime_error &e) {
        caught = true;
    }
    assert(caught && "Expected division by zero exception.");
}

/**
 * Tests handling of an invalid token in a postfix expression.
 * The expression "4,5,?,+" should throw a runtime_error.
 */
void testInvalidToken() {
    bool caught = false;
    try {
        PostFixCalculator("4,5,?,+");
    } catch (const std::runtime_error &e) {
        caught = true;
    }
    assert(caught && "Expected invalid token exception.");
}

/**
 * Runs all PostFixCalculator tests.
 * Calls each individual test function and prints a message upon successful completion.
 */
void Test::testPostFixCalculator() {
    testAddition();
    cout << "Addition test passed." << endl;

    testMultiplication();
    cout << "Multiplication test passed." << endl;

    testSubtractionWithGrouping();
    cout << "Subtraction with grouping test passed." << endl;

    testComplexExpression();
    cout << "Complex expression test passed." << endl;

    testDivision();
    cout << "Division test passed." << endl;

    testDivisionByZero();
    cout << "Division by zero test passed." << endl;

    testInvalidToken();
    cout << "Invalid token test passed." << endl;

    cout << "All PostFixCalculator tests passed successfully." << endl;
}
