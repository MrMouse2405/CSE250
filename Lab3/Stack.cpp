/******************************************************************************
 * Stack.cpp
 *
 *  Created on:
 *      Author: YOUR NAME
 *
 *  Implementation details:
 *      This Stack uses a LinkedList (which is assumed to be a doubly linked list)
 *      as its underlying container. The top of the stack is the head of the list.
 *      Push and Pop operate in O(1). The PrintStack method traverses the list
 *      and prints each element on its own line, from top (head) to bottom.
 *
 ******************************************************************************/

#include "Stack.h"
#include <iostream>
using namespace std;

/** Constructs an empty stack. */
Stack::Stack() : m_List(LinkedList())
{
}

/** Deletes the stack. */
Stack::~Stack()
{
	// m_List will clean up its nodes via its destructor.
}

/** Indicates whether the stack is empty in O(1).
 *  @return true if empty, false otherwise.
 */
bool Stack::IsEmpty()
{
	return m_List.Length() == 0;
}

/** Prints all the elements of the stack using cout, from top to bottom (one per line).
 *  Time Complexity: O(n), where n is the number of elements in the stack.
 */
void Stack::PrintStack()
{
	int len = m_List.Length();
	for (int i = 0; i < len; i++)
	{
		cout << m_List.GetValueAt(i) << "\n";
	}
}

/** Adds a string on the top of the stack in O(1).
 *  @param new_value New string to push onto the stack.
 */
void Stack::Push(const string &new_value)
{
	m_List.InsertFirst(new_value);
}

/** Removes and returns the string on the top of the stack in O(1).
 *  @return The string on top of the stack or "" if empty.
 */
string Stack::Pop()
{
	return m_List.RemoveFirst();
}

/** Returns the string on the top of the stack in O(1).
 *  @return The string on top of the stack or "" if empty.
 */
string Stack::Top()
{
	return m_List.GetValueAt(0);
}
