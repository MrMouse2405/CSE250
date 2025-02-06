/****************************************************************************\
 * LinkedList.h
 *
 *  Created on: Feb, 06, 2025
 *      Author: OCdt Syed
 *
 *
 *  Implementation details: ?
 *
 \***************************************************************************/

#pragma once
#include <string>
#include <optional>
using namespace std;

/** Doubly linked-list node. */
struct Node
{
	/** String of data. */
	string value;
	/** Pointer to next node. */
	optional<Node *> next;
	/** Pointer to previous node. */
	optional<Node *> prev;

	Node(string value, optional<Node *> next, optional<Node *> previous) : value(value), next(next), prev(previous) {}
};

/** Linked-list of string class. */
class LinkedList
{
private:
	/** Pointer to the first node. */
	optional<Node *> m_First = nullopt;
	optional<Node *> cursor = nullopt;
	size_t lenght = 0;
	size_t cursorIdx = 0;

public:
	/** Constructs an empty list. */
	LinkedList();
	/** Deletes an empty list by freeing nodes memory. */
	virtual ~LinkedList();

	/** Returns the length of the list in O(1). */
	int Length();
	/** Prints all the element of the list using cout, on a single line, separated by a comma. eg: [3, 19, 2, 36].*/
	void PrintList();

	/** Inserts a new string in first position in O(1). */
	void InsertFirst(const string &new_value);
	/** Removes and returns the first element of the list in O(1). Returns "" if empty. */
	string RemoveFirst();

	/** Returns the string at a given index (1st node at index 0, 2nd at index 1, etc...) in O(n).
	 *  Returns "" if the index does not exist. */
	string GetValueAt(int index);
};
