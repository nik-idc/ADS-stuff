#ifndef STACK_H
#define STACK_H

#include "nodes.h"

/*
	Stack:                       Top
		       A1 <- A2 <- A3 <- A4
	Insert:                      Top                            Top
			   A1 <- A2 <- A3 <- A4 =>  A1 <- A2 <- A3 <- A4 <- A5
	Delete:                            Top                      Top
			   A1 <- A2 <- A3 <- A4 <- A5 =>  A1 <- A2 <- A3 <- A4
*/

template <typename t>
class stack
{
public:
	// Constructor
	stack()
	{
		top = NULL;
		size_v = 0;
	}

	// Construct from existing array
	stack(int *arr, int size)
	{
		top = NULL;
		this->size_v = 0;

		for (int i = 0; i < size; i++)
			push(0);

		sqnode<t> *cur = top;

		for (int i = size - 1; i >= 0; i--)
		{
			cur->data = arr[i];
			cur = cur->link;
		}
	}

	// Copy constructor
	stack(const stack &toCopy)
	{
		top = NULL;
		this->size_v = 0;

		for (int i = 0; i < toCopy.size_v; i++)
			push(0);

		sqnode<t> *curR = toCopy.top;
		sqnode<t> *curL = top;
		for (int i = 0; i < toCopy.size_v; i++)
		{
			curL->data = curR->data;
			curL = curL->link;
			curR = curR->link;
		}
	}

	// Destructor
	~stack()
	{
		if (!isEmpty())
			clear();
		top = NULL;
	}

	// Add an element to the stack
	void push(t data)
	{
		sqnode<t> *temp = new sqnode<t>;
		temp->data = data;

		temp->link = top;
		top = temp;
		size_v++;
	}

	// Delete element from stack
	t pop()
	{
		if (!isEmpty())
		{
			t temp = top->data;
			sqnode<t> *prev = top->link;

			delete top;
			top = prev;

			size_v--;
			return temp;
		}
	}

	// Return top element
	t getTop()
	{
		if (!isEmpty())
			return top->data;
	}

	// Return the index of an element with data 'toFind'
	int find(t toFind)
	{
		if (!isEmpty())
		{
			sqnode<t> *cur = top;
			size_t i = size_v - 1;
			while (cur != NULL && cur->data != toFind)
			{
				cur = cur->link;
				i--;
			}

			if (cur == NULL)
				return -1;
			else
				return i;
		}
		else
			return -1;
	}

	// Check if the stack is empty
	bool isEmpty()
	{
		if (top)
			return false;
		else
			return true;
	}

	// Clear the stack
	void clear()
	{
		while (!isEmpty())
			pop();
	}

	// Return size of the stack
	int size()
	{
		return size_v;
	}

	// [] operator overload
	t &operator[](int ind)
	{
		if (ind >= 0 && ind < size_v)
		{
			int i = size_v - 1;
			sqnode<t> *current = top;
			for (; i != ind; i--)
				current = current->link;
			return current->data;
		}
	}

	// = operator overload
	stack &operator=(const stack &rightStack)
	{
		clear();

		for (int i = 0; i < rightStack.size_v; i++)
			push(0);

		sqnode<t> *curR = rightStack.top;
		sqnode<t> *curL = top;
		for (int i = 0; i < rightStack.size_v; i++)
		{
			curL->data = curR->data;
			curL = curL->link;
			curR = curR->link;
		}

		return *this;
	}

	// == operator overload
	bool operator==(const stack &rightStack)
	{
		if (size_v == rightStack.size_v)
		{
			sqnode<t> *curL = top;
			sqnode<t> *curR = rightStack.top;
			while (curL != NULL)
			{
				if (curL->data != curR->data)
					return false;
				else
				{
					curL = curL->link;
					curR = curR->link;
				}
			}
			return true;
		}
		else
			return false;
	}

	class stackIterator : public iterator<t>
	{
	public:
		stackIterator(size_t start, stack<t> &st)
		{
			if (start >= 0 && start < st.size())
			{
				size_t i = st.size() - 1;
				current = st.top;
				while (i != start && current != NULL)
				{
					current = current->link;
					i--;
				}
			}
			else
				throw std::invalid_argument("Can't start iterating the list at specified index!");
		}

		~stackIterator()
		{
			delete this;
		}

		t &next() override
		{
			if (hasNext())
			{
				t &temp = current->data;
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
		return new stackIterator(start, *this);
	}
private:
	// The top sqnode
	sqnode<t> *top;
	// Size variable
	size_t size_v;
};

#endif