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

#include <iostream>
#include "PostFixCalculator.h"
#include "Test.h"

using namespace std;

void testAddition() {
    cout << "Testing addition: 4,5,+" << endl;
    cout << "Result: " << PostFixCalculator("4,5,+") << " (expected: 9)" << endl;
}

void testMultiplication() {
    cout << "Testing multiplication: 3,9,*" << endl;
    cout << "Result: " << PostFixCalculator("3,9,*") << " (expected: 27)" << endl;
}

void testSubtractionWithGrouping() {
    cout << "Testing subtraction with grouping: 2,5,3,+,-" << endl;
    cout << "Result: " << PostFixCalculator("2,5,3,+,-") << " (expected: -6)" << endl;
}

void testComplexExpression() {
    cout << "Testing complex expression: 1,5,+,8,4,1,-,-,*" << endl;
    cout << "Result: " << PostFixCalculator("1,5,+,8,4,1,-,-,*") << " (expected: 30)" << endl;
}

void testDivision() {
    cout << "Testing division: 10,2,/" << endl;
    cout << "Result: " << PostFixCalculator("10,2,/") << " (expected: 5)" << endl;
}

void testDivisionByZero() {
    cout << "Testing division by zero: 10,0,/" << endl;
    try {
        PostFixCalculator("10,0,/");
        cout << "Expected division by zero exception but none occurred." << endl;
    } catch (const runtime_error &e) {
        cout << "Caught expected division by zero exception." << endl;
    }
}

void testInvalidToken() {
    cout << "Testing invalid token: 4,5,?,+" << endl;
    try {
        PostFixCalculator("4,5,?,+");
        cout << "Expected invalid token exception but none occurred." << endl;
    } catch (const runtime_error &e) {
        cout << "Caught expected invalid token exception." << endl;
    }
}

void Test::testPostFixCalculator() {
    testAddition();
    testMultiplication();
    testSubtractionWithGrouping();
    testComplexExpression();
    testDivision();
    testDivisionByZero();
    testInvalidToken();
}
