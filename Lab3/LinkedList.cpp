/****************************************************************************\
 * LinkedList.h
 *
 *  Created on:
 *      Author: YOUR NAME
 *
 *
 *  Implementation details: ?
 *  \\TODO
 *  You can add your implementation details here or in the header,
 *  or with appropriate variable's or function's comments.
 *
 \***************************************************************************/

#include "LinkedList.h"

#include <iostream>
#include <assert.h>
using namespace std;

/** Constructs an empty list.  */
LinkedList::LinkedList() {
};

/** Deletes an empty list by freeing nodes memory. */
LinkedList::~LinkedList()
{
	while (Length() > 0)
	{
		RemoveFirst();
	}
}

/** Returns the length of the list in O(1).
 * Return: Length of the list
 */
int LinkedList::Length()
{
	return this->lenght;
}

/** Prints all the element of the list using cout, on a single line, separated by a comma. eg: [3, 19, 2, 36].*/
void LinkedList::PrintList()
{

	if (m_First == nullptr)
	{
		cout << "[]" << endl;
		return;
	}

	cout << "[";

	optional<Node *> walker = m_First;
	for (;;)
	{
		cout << walker.value()->value;
		walker = walker.value()->next;
		if (walker.has_value())
		{
			cout << ",";
		}
		else
		{
			break;
		}
	}
	cout << "]" << endl;
}

/** Inserts a new string in first position in O(1).
 * Args: new_value is the new string to put in the list
 */
void LinkedList::InsertFirst(const string &new_value)
{
	if (this->lenght == 0)
	{
		m_First = optional(new Node(new_value, nullopt, nullopt));
		return;
	}

	auto toShift = m_First;

	m_First = optional(new Node(new_value, nullopt, m_First));
	toShift.value()->prev = m_First;

	this->lenght += 1;
}

/** Removes and returns the first element of the list in O(1).
 * Return: The string removed, or "" if empty
 */
string LinkedList::RemoveFirst()
{
	assert(lenght > -1 && "OUT OF BOUNDS");
	switch (lenght)
	{
	case 0:
	{
		return "";
	}
	break;
	case 1:
	{
		assert(m_First.has_value() && "VALUE DOES NOT EXIST!");

		const string toReturn = m_First.value()->value;
		m_First.reset();

		lenght -= 1;
		return toReturn;
	}
	break;
	default:
	{
		assert(m_First.has_value() && "VALUE DOES NOT EXIST!");

		const string toReturn = m_First.value()->value;
		const optional<Node *> toShift = m_First.value()->next;

		assert(toShift.has_value() && "NEXT VALUE DOES NOT EXIST!");

		m_First.reset();
		m_First = toShift;
		m_First.value()->prev.reset();

		lenght -= 1;
		return toReturn;
	}
	break;
	}
}

/** Returns the string at a given index (1st node at index 0, 2nd at index 1, etc...) in O(n).
 *  Args: index node position =  1st node at index 0, 2nd at index 1, etc...
 *  Return: "" if the index does not exists */
string LinkedList::GetValueAt(int index)
{
	if (index < 0 || index > lenght)
	{
		return "";
	}

	auto walker = m_First;
	for (size_t idx = 0; idx < lenght; idx++)
	{
		if (!walker.has_value())
		{
			throw std::logic_error("Index " + to_string(idx) + " has empty value!");
		}
		walker = m_First.value()->next;
	}

	return walker.value()->value;
}
