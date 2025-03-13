/******************************************************************************
* PostFixCalculator.h
 *
 *  Created on: Feb 13 2025
 *      Author: OCdt Syed
 *
 *  Implementation details:
 *      Declares the function for evaluating a postfix expression.
 *
 ******************************************************************************/

#pragma once
#include <string>

/**
 * Computes and returns the result from an equation in postfix notation.
 * Throws a runtime_error if the equation is malformed.
 * @param equation The postfix expression as a string.
 * @return The result of the postfix calculation.
 */
double PostFixCalculator(const std::string &equation);
