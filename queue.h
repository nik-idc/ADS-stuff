#pragma once
#ifndef QUEUE_H
#define QUEUE_H

#include "nodes.h"
//#include <fstream>

/*
	Queue:     Front             Rear
			   A1 -> A2 -> A3 -> A4
	Insert:    Front             Rear     Front                   Rear
			   A1 -> A2 -> A3 -> A4   =>  A1 -> A2 -> A3 -> A4 -> A5
	Delete:    Front                   Rear     Front             Rear
			   A1 -> A2 -> A3 -> A4 -> A5   =>  A2 -> A3 -> A4 -> A5
*/

template <typename t>
class queue
{
public:

	// Basic constructor
	queue()
	{
		front = NULL;
		rear = NULL;
		size_v = 0;
	}

	// Destructor
	~queue()
	{
		clear();
	}

	// Copy constructor
	queue(const queue &toCopy)
	{
		front = NULL;
		rear = NULL;
		size_v = 0;

		for (int i = 0; i < toCopy.size_v; i++)
			enqueue("0");

		sqnode<t> *curR = toCopy.front;
		sqnode<t> *curL = front;
		for (int i = 0; i < toCopy.size_v; i++)
		{
			curL->data = curR->data;
			curL = curL->link;
			curR = curR->link;
		}
	}

	// Enqueue
	void enqueue(t data)
	{
		sqnode<t> *temp = new sqnode<t>;
		temp->data = data;

		if (!front)
		{
			front = temp;
			front->link = NULL;
		}
		else if (front && !rear)
		{
			rear = temp;
			front->link = rear;
			rear->link = NULL;
		}
		else
		{
			rear->link = temp;
			rear = temp;
			rear->link = NULL;
		}

		size_v++;
	}

	// Dequeue
	void dequeue()
	{
		if (!empty())
		{
			if (front && !rear)
			{
				delete front;
				front = NULL;
			}
			else if (front->link == rear)
			{
				delete front;
				front = rear;
				rear = NULL;
			}
			else
			{
				sqnode<t> *temp = front->link;
				delete front;
				front = temp;
			}

			size_v--;
		}
	}

	// Check if queue is empty
	bool empty()
	{
		if (front)
			return false;
		else
			return true;
	}

	// Returns the size of the queue
	int size()
	{
		return size_v;
	}

	// Reverses the queue
	void reverse(bool toChangePars)
	{
		if (!empty())
		{
			t temp;
			int start = 0, end = size() - 1;

			while (end - start > 0)
			{
				t = (*this)[start];
				(*this)[start] = (*this)[end];
				(*this)[end] = temp;
				start++; end--;
			}

			if (toChangePars)
			{
				sqnode<t> *cur = front;
				while (cur->link != NULL)
				{
					if (cur->data == "(")
						cur->data = ")";
					else if (cur->data == ")")
						cur->data = "(";
					cur = cur->link;
				}
			}
		}
	}

	// Returns front element
	t peek()
	{
		if (!empty())
			return front->data;
	}

	// Clears the queue
	void clear()
	{
		if (!empty())
		{
			int i = 0, s = size_v;
			while (i < s)
			{
				dequeue();
				i++;
			}
		}
	}

	// Prints all elements
	void print()
	{
		if (!empty())
		{
			sqnode<t> *cur = front;
			while (cur->link != NULL)
			{
				std::cout << cur->data << '\t';
				cur = cur->link;
			}
		}
	}

	// [] opeartor for queue
	t &operator[](int ind)
	{
		if (ind <= size_v && !empty())
		{
			sqnode<t> *cur = front;
			int i = 0;
			while (i < ind)
			{
				cur = cur->link;
				i++;
			}
			return cur->data;
		}
	}

	// = operator overload
	queue &operator=(const queue &right)
	{
		clear();

		for (int i = 0; i < right.size_v; i++)
			enqueue("0");

		sqnode<t> *curR = right.front;
		sqnode<t> *curL = front;
		while (curL != NULL)
		{
			curL->data = curR->data;
			curL = curL->link;
			curR = curR->link;
		}

		return *this;
	}

	friend std::ostream &operator<<(std::ostream &os, const queue &toOut)
	{
		sqnode<t> *cur = toOut.front;
		while (cur->link != NULL)
		{
			os << cur->data;
			cur = cur->link;
		}

		return os;
	}

	class queueIterator : public iterator<t>
	{
	public:
		queueIterator(size_t start, queue<t> &st)
		{
			if (start >= 0 && start < st.size())
			{
				size_t i = 0;
				current = st.front;
				while (i != start && current != NULL)
				{
					current = current->link;
					i++;
				}
			}
			else
				throw std::invalid_argument("Can't start iterating the list at specified index!");
		}

		~queueIterator()
		{
			delete this;
		}

		t next() override
		{
			if (hasNext())
			{
				t temp = current->data;
				current = current->link;
				return temp;
			}
		}

		bool hasNext() override
		{
			if (current)
				return true;
			else
				return false;
		}
	private:
		sqnode<t> *current;
	};

	iterator<t> *createIterator(size_t start)
	{
		return new queueIterator(start, *this);
	}

private:
	// Front pointer
	sqnode<t> *front;
	// Rear pointer
	sqnode<t> *rear;
	// Size variable
	int size_v;
};
#endif