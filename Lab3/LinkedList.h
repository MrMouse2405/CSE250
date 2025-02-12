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

/** Doubly linked-list node. */
struct Node
{
	/** String of data. */
	std::string value;
	/** Pointer to next node. */
	std::optional<Node *> next;
	/** Pointer to previous node. */
	std::optional<Node *> prev;

	Node(std::string value, std::optional<Node *> next, std::optional<Node *> previous) : value(value), next(next), prev(previous) {}
};

/** Linked-list of string class. */
class LinkedList
{
private:
	/** Pointer to the first node. */
	std::optional<Node *> m_First = std::nullopt;
	std::optional<Node *> cursor = std::nullopt;
	std::size_t length = 0;
	std::size_t cursorIdx = 0;

public:
	/** Constructs an empty list. */
	LinkedList();
	/** Deletes an empty list by freeing nodes memory. */
	virtual ~LinkedList();

	/** Returns the length of the list in O(1). */
	std::size_t Length();
	/** Prints all the element of the list using cout, on a single line, separated by a comma. eg: [3, 19, 2, 36].*/
	void PrintList();

	/** Inserts a new string in first position in O(1). */
	void InsertFirst(const std::string &new_value);
	/** Removes and returns the first element of the list in O(1). Returns "" if empty. */
	std::string RemoveFirst();

	/** Returns the string at a given index (1st node at index 0, 2nd at index 1, etc...) in O(n).
	 *  Returns "" if the index does not exist. */
	std::string GetValueAt(const std::size_t index);
};
