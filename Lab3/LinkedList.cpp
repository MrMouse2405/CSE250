/******************************************************************************
 * LinkedList.cpp
 *
 *  Created on:
 *      Author: OCdt Syed
 *
 *  Implementation details:
 *     This implementation uses a doubly linked list where the head is stored in
 *     an optional pointer. The optional wrappers are used to indicate the presence
 *     or absence of a pointer. Memory for new nodes is allocated with new and freed
 *     with delete.
 *
 ******************************************************************************/

#include "LinkedList.h"

#include <iostream>
#include <cassert>
#include <stdexcept>
using namespace std;

/** Constructs an empty list.  */
LinkedList::LinkedList()
	: m_First(nullopt), length(0)
{
}

/** Deletes the list by repeatedly removing the first element until empty. */
LinkedList::~LinkedList()
{
	while (Length() > 0)
	{
		RemoveFirst();
	}
}

/** Returns the length of the list in O(1).
 *  @return length of the list.
 */
size_t LinkedList::Length()
{
	return length;
}

/** Prints all the elements of the list using cout, on a single line,
 *  separated by a comma. e.g.: [3,19,2,36].
 */
void LinkedList::PrintList()
{
	if (!m_First.has_value())
	{
		cout << "[]" << endl;
		return;
	}

	cout << "[";
	optional<Node *> walker = m_First;
	bool firstElement = true;
	while (walker.has_value())
	{
		if (!firstElement)
		{
			cout << ",";
		}
		cout << walker.value()->value;
		walker = walker.value()->next;
		firstElement = false;
	}
	cout << "]\n";
}

/** Inserts a new string in first position in O(1).
 *  @param new_value the new string to put in the list.
 */
void LinkedList::InsertFirst(const string &new_value)
{
	// Create a new node whose next pointer is the current first node.
	Node *newNode = new Node(new_value, m_First, nullopt);

	// If the list is not empty, update the current first node's previous pointer.
	if (m_First.has_value())
	{
		m_First.value()->prev = newNode;
	}
	// Update m_First to point to the new node.
	m_First = newNode;
	length++;
}

/** Removes and returns the first element of the list in O(1).
 *  @return the string removed, or an empty string if the list is empty.
 */
string LinkedList::RemoveFirst()
{
	if (length == 0 || !m_First.has_value())
	{
		return "";
	}

	Node *nodeToRemove = m_First.value();
	string returnValue = nodeToRemove->value;

	if (nodeToRemove->next.has_value())
	{
		m_First = nodeToRemove->next.value();
		m_First.value()->prev.reset();
	}
	else
	{
		m_First.reset();
	}

	delete nodeToRemove;
	length--;
	return returnValue;
}

/** Returns the string at a given index (0-based indexing).
 *  If the index does not exist, returns an empty string.
 *  @param index the index of the node.
 *  @return the value at that index, or "" if out-of-bounds.
 */
string LinkedList::GetValueAt(const size_t index)
{
	if (index < 0 || index >= length)
	{
		return "";
	}

	optional<Node *> walker = m_First;
	for (int idx = 0; idx < index; idx++)
	{
		if (!walker.has_value())
		{
			// This situation should not happen.
			throw std::logic_error("Invalid internal state: missing node at index " + to_string(idx));
		}
		walker = walker.value()->next;
	}

	if (!walker.has_value())
	{
		return "";
	}
	return walker.value()->value;
}
