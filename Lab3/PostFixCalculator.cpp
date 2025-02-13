/******************************************************************************
 * PostFixCalculator.cpp
 *
 *  Created on: 13 Feb 2025
 *      Author: OCdt Syed
 *
 *  Implementation details:
 *      Implements a postfix calculator for lab 3 using a generic Stack.
 *
 ******************************************************************************/

#include <sstream>
#include <stdexcept>
#include <cassert>
#include "PostFixCalculator.h"
#include "Stack.h"

/**
 * Computes and returns the result from an equation in postfix notation.
 * Throws a runtime_error if the equation is malformed.
 * @param equation The postfix equation as a string.
 * @return The computed result as a double.
 */
double PostFixCalculator(const std::string &equation) {
    Stack<double> stack;
    std::istringstream iss(equation);
    std::string token;

    while (std::getline(iss, token, ',')) {
        if (token.empty())
            continue;

        if (token == "+" || token == "-" || token == "*" || token == "/") {
            auto val2 = stack.Pop();
            auto val1 = stack.Pop();
            assert(val1.has_value() && val2.has_value() && "Stack has less than 2 values");

            const double operand1 = val1.value();
            const double operand2 = val2.value();
            double result = 0.0;

            if (token == "+") {
                result = operand1 + operand2;
            } else if (token == "-") {
                result = operand1 - operand2;
            } else if (token == "*") {
                result = operand1 * operand2;
            } else if (token == "/") {
                if (operand2 == 0.0)
                    throw std::runtime_error("Division by zero error.");
                result = operand1 / operand2;
            }
            stack.Push(result);
        } else {
            try {
                double number = std::stod(token);
                stack.Push(number);
            } catch (const std::exception &e) {
                throw std::runtime_error("Invalid token: " + token);
            }
        }
    }

    auto finalVal = stack.Pop();
    return finalVal.value_or(0);
}
