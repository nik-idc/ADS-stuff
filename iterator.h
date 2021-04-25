#pragma once
#ifndef ITERATOR_H
#define ITERATOR_H

template <typename t>
class iterator // Base iterator class
{
public:
	virtual t next() = 0; // Returns the next element
	virtual bool hasNext() = 0; // Checks whether next element exists
};

#endif