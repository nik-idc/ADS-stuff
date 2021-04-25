#ifndef NODE_H
#define NODE_H

#include "iterator.h"
#include <iostream>
#include <fstream>
#include <string>

// Node class for stack and queue
template <typename t>
class sqnode
{
public:
	t data; // Basic data block
	sqnode<t> *link; // A pointer for linking stacks/queues. In the case of 'stack' points to the previous element, whereas in the case of 'queue' points to next element

	sqnode() // Basic node constructor
	{
		data = t();
		link = NULL;
	}

	sqnode(const int num) // Basic NULL constructor of node class
	{
		if (num == NULL)
			sqnode();
		else
			throw std::invalid_argument("NULL initialization failed");
	}
};

template <typename t>
class lnode
{
public:
	t data; // Data variable to store whatever the user wants to store
	lnode<t> *next; // Pointer to next element
	lnode<t> *prev; // Pointer to previous element

	lnode() // Basic constructor of node class
	{
		data = t();
		next = NULL;
		prev = NULL;
	}

	lnode(const int num) // Basic NULL constructor of node class
	{
		if (num == NULL)
			lnode();
		else
			throw std::invalid_argument("NULL initialization failed");
	}
};
#endif