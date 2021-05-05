#pragma once
#ifndef LIST_H
#define LIST_H

#include "nodes.h"

template <typename t>
class list
{
public:
	// Basic constructor of list class. Assignes NULL to head and tail
	list()
	{
		head = NULL;
		tail = NULL;
		size_v = 0;
	}

	list(const list &toCopy)
	{
		head = NULL;
		tail = NULL;
		size_v = 0;

		lnode<t> *curCopy = toCopy.head;
		for (int i = 0; i < toCopy.size_v; i++)
		{
			pushBack(curCopy->data);
			curCopy = curCopy->next;
		}
	}

	// 'list' class object destructor
	~list()
	{
		clear();
	}

	// Adds an element at the end of the list
	void pushBack(t data)
	{
		if (!head)
		{
			head = new lnode<t>;
			head->prev = NULL;
			head->next = NULL;
			head->data = data;
		}
		else
		{
			lnode<t> *newTail = new lnode<t>, *last;

			if (tail)
				last = tail;
			else
				last = head;

			newTail->prev = last;
			last->next = newTail;
			newTail->data = data;
			tail = newTail;
		}
		size_v++;
	}

	// Adds an element at the start of the list
	void pushFront(t data)
	{
		if (!head)
		{
			head = new lnode<t>;
			head->prev = NULL;
			head->next = NULL;
			head->data = data;
		}
		else
		{
			lnode<t> *newHead = new lnode<t>;

			newHead->prev = NULL;
			newHead->next = head;
			newHead->data = data;
			head->prev = newHead;
			head = newHead;

			if (!tail)
			{
				tail = head->next;
				tail->prev = head;
			}
		}
		size_v++;
	}

	// Removes an element at the end of the list
	void popBack()
	{
		if (head && !tail)
		{
			delete head;
			head = NULL;
		}
		else if (head && tail)
		{
			lnode<t> *temp = tail->prev;
			tail->prev->next = NULL;
			delete tail;
			tail = temp;
			if (tail == head)
				tail = NULL;
		}
		size_v--;
	}

	// Removes an element at the start of the list
	void popFront()
	{
		if (head && !tail)
		{
			delete head;
			head = NULL;
		}
		else if (head && tail)
		{
			lnode<t> *temp = head->next;
			head->next->prev = NULL;
			delete head;
			head = temp;
			if (tail == head)
				tail = NULL;
		}
		size_v--;
	}

	// Inserts a new element with elements's data being 'data' inside the list at index 'index'
	void insert(t data, int index)
	{
		if (index >= 1 && index <= size() + 1) // Can't get an element if it's outside the list
		{
			if (index == 1)
				pushFront(data);
			else if (index == size() + 1)
				pushBack(data);
			else
			{
				lnode<t> *current = head;
				int k = 1;
				while (k != index - 1)
				{
					current = current->next;
					k++;
				}

				lnode<t> *newAtIndex = new lnode<t>;
				lnode<t> *preIndex = current;
				lnode<t> *postIndex = current->next;

				preIndex->next = newAtIndex;
				postIndex->prev = newAtIndex;

				newAtIndex->next = postIndex;
				newAtIndex->prev = preIndex;
				newAtIndex->data = data;
				size_v++;
			}
		}
		else
			throw std::out_of_range("Can't add an element at specified index!");
	}

	// Removes an element at index 'index' from the list
	void remove(int index)
	{
		if (index >= 1 && index <= size() && !isEmpty()) // Can't get an element if it's outside the list
		{
			if (index == 1)
				popFront();
			else if (index == size())
				popBack();
			else
			{
				lnode<t> *current = head;
				int k = 1;
				while (k != index)
				{
					current = current->next;
					k++;
				}

				lnode<t> *preIndex = current->prev;
				lnode<t> *atIndex = current;
				lnode<t> *postIndex = current->next;

				preIndex->next = postIndex;
				postIndex->prev = preIndex;
				delete atIndex;
				size_v--;
			}
		}
		else
			throw std::out_of_range("Can't remove node at specified index!");
	}

	// Return the index of an element with data 'toFind'
	int find(t toFind)
	{
		if (!isEmpty())
		{		
			lnode<t> *cur = head;

			int i = 0;
			while (cur != NULL && cur->data != toFind)
			{
				cur = cur->next;
				i++;
			}

			if (!cur)
				return -1;
			else
				return i;
		}
		else
			return -1;
	}

	// Return the size of the current list
	int size()
	{
		return size_v;
	}

	// Checks if the list is empty. As long as head is not NULL list is considered initialised
	bool isEmpty()
	{
		if (head)
			return false;
		else
			return true;
	}

	// Removes all elements from the list
	void clear()
	{
		if (!isEmpty())
		{
			lnode<t> *current = head;
			lnode<t> *del;
			while (current != NULL)
			{
				del = current;
				current = current->next;
				delete del;
			}
			head = NULL;
			tail = NULL;
			size_v = 0;
		}
	}

	list &operator=(const list &right)
	{
		clear();
		lnode<t> *current = right.head;
		while (current != NULL)
		{
			pushBack(current->data);
			current = current->next;
		}
		return *this;
	}

	t &operator[](int index)
	{
		if (!isEmpty() && index >= 0 && index <= size_v - 1)
		{
			lnode<t> *current = head;
			int k = 0;
			while (k != index)
			{
				current = current->next;
				k++;
			}
			return current->data;
		}
		else
			throw std::out_of_range("Item at specified index does not exist");
	}

	class listIterator : public iterator<t>
	{
	public:
		listIterator(size_t start, list<t> &l)
		{
			if (start >= 0 && start < l.size())
			{
				size_t i = 0;
				current = l.head;
				while (i != start && current != NULL)
				{
					current = current->next;
					i++;
				}
			}
			else
				throw std::invalid_argument("Can't start iterating the list at specified index!");
		}

		~listIterator()
		{
			delete this;
		}

		t &next() override
		{
			if (hasNext())
			{
				t &temp = current->data;
				current = current->next;
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
		lnode<t> *current;
	};

	iterator<t> *createIterator(size_t start)
	{
		return new listIterator(start, *this);
	}

private:
	lnode<t> *head; // Head of the list
	lnode<t> *tail; // Tail of the list
	size_t size_v;
};

#endif