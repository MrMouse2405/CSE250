/****************************************************************************\
 * Queue.h
 *
 *  Created on:
 *      Author: YOUR NAME
 *
 *
 *  Implementation details: ?
 *
 \***************************************************************************/

#pragma once
#include <memory>

/** Queue of integers using an array. */
class Queue
{

private:
	/** Array used as a circular buffer for queue content. */
	const std::unique_ptr<int[]> m_Data;
	/** Size of the circular buffer. */
	const std::size_t m_MaxSize;
	/** TODO PLEASE DESCRIBE */
	std::size_t m_First;
	/** TODO PLEASE DESCRIBE */
	std::size_t size;
	// TODO: Add other instance variables or helper methods if needed

public:
	/** Constructs an empty queue of maximum size new_max_size */
	explicit Queue(std::size_t new_max_size);
	/** Deletes the queue and free up its memory. */
	virtual ~Queue();

	/** Indicates whether of not the queue is empty in O(1), true if empty, false if not. */
	bool IsEmpty();
	/** Indicates whether of not the queue is full in O(1), true if full, false if not. */
	bool IsFull();

	/** Prints the content of the queue on a single line, separated by comma, eg: [3, 19, 2, 36]. */
	void PrintQueue();

	/** Inserts an element at the end of the queue, returns true if succeed, and false if the queue is already full. */
	bool Enqueue(int new_value);
	/** Removes the element at the front of the queue and returns the element in the argument,
	 * returns true if succeed, and false if the queue is already full.  */
	bool Dequeue(int &old_value);
};
