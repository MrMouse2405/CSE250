/****************************************************************************\
 * Stack.h
 *
 *  Created on:
 *      Author: YOUR NAME
 *
 *
 *  Implementation details: ?
 *
 \***************************************************************************/

#pragma once
#include <string>

#include "LinkedList.h"

/** Stack of strings using linked-list. */
class Stack
{
private:
	/** LinkedList variable (not a pointer), therefore enough space is already allocated
	 * and the constructor and destructor are automatically called when constructing
	 * or destructing the Stack object. */
	mutable LinkedList m_List;

public:
	/** Constructs an empty stack. */
	Stack();
	/** Deletes the stack. */
	virtual ~Stack();

	/** Indicates whether the stack is empty (true) or not (false) in O(1). */
	bool IsEmpty();
	/** Prints all the element of the stack using cout, from top to bottom (1 item per line). */
	void PrintStack();

	/** Adds a string on the top of the stack in O(1).*/
	void Push(const std::string &new_value);
	/** Removes and returns the string on the top of the stack in O(1). Returns "" if empty. */
	std::string Pop();
	/** Returns the string on the top of the stack in O(1). Returns "" if empty .*/
	std::string Top();
};
