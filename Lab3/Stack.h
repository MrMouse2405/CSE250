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

#ifndef STACK_H_
#define STACK_H_

#include "LinkedList.h"

#include <string>
using namespace std;

/** Stack of strings using linked-list. */
class Stack
{
private:
	/** LinkedList variable (not a pointer), therefore enough space is already allocated
	 * and the constructor and destructor are automatically called when constructing
	 * or destructing the Stack object. */
	unique_ptr<LinkedList> m_List;

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
	void Push(const string &new_value);
	/** Removes and returns the string on the top of the stack in O(1). Returns "" if empty. */
	string Pop();
	/** Returns the string on the top of the stack in O(1). Returns "" if empty .*/
	string Top();
};

#endif /* STACK_H_ */
