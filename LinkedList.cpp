///cygdrive/C/Users/lachl/OneDrive/Documents/Uni/SENG1120_Assessment/Assignment1

#include <iostream>
using namespace std;
#include "LinkedList.h"
typedef Node::value_type value_type;

LinkedList::LinkedList()
{
	head = NULL;
	tail = NULL;
	current = NULL;
	size = 0;
}
LinkedList::~LinkedList()
{}

int LinkedList::getSize() const
{
	return size;
}

void LinkedList::addToTail(value_type* data_)
{
	if ((head == NULL) && (tail == NULL))
	{
		head = new Node(data_);
		tail = head;
		size++;
	}
	else
	{
		current = new Node(data_);
		current->setPrev(tail);
		tail->setNext(current);
		tail = current;
		size++;
	}
}

void LinkedList::add(value_type data)
{
	value_type* temp = new value_type();
	for (long unsigned int i = 0; i < data.length(); i++)
	{
		if (data[i] == ' ')
		{
			addToTail(temp);
			temp = new value_type();
		}
		else
		{
			*temp += data[i];
		}
	}
	addToTail(temp);
	temp = NULL;
}

void LinkedList::addToHead(value_type* data_)
{
	if ((head == NULL) && (tail == NULL))
	{
		tail = new Node(data_);
		head = tail;
		size++;
	}
	else
	{
		current = new Node(data_);
		current->setNext(head);
		head->setPrev(current);
		head = current;
		size++;
	}
}

void LinkedList::remove(value_type identifier)
{
	if ((head == NULL) && (tail == NULL))
	{
		return;
	}
	
	jumpToHead();
	bool identified = false;
	do
	{
		
		if (identifier == *getCurrent())
		{
			identified = true;
			
			if (head == tail)
			{
				current = head;
				head = NULL;
				tail = NULL;
			}
			else if (current == head)
			{
				head = current->getNext();
				head->setPrev(NULL);
		
			}
			else if (current == tail)
			{
				tail = current->getPrev();
				tail->setNext(NULL);
		
			}
			else
			{
				current->getPrev()->setNext(current->getNext());
				current->getNext()->setPrev(current->getPrev());
			}
			delete(current);
			current = head;
		}
	}
	while (moveNext() == 0);
	
	if (!identified)
	{
		cout << "No such item in list" << endl;
		return;
	}
}

int LinkedList::count(const value_type identifier)
{
	int occurrences = 0;
	if (jumpToHead() == -1)
	{
		return -1;
	}
	do
	{
		if (identifier == *getCurrent())
		{
			occurrences++;
		}
	}
	while (moveNext() == 0);
	return occurrences;
}

void LinkedList::sort()
{
	string a;
	string b;
	//Node* temp;
	bool restart = false;

		for (current = head; current->getNext() != NULL; moveNext())
		{
			if (restart)
			{
				jumpToHead();
				restart = false;
			}
			a = *current->getData();
			b = *current->getNext()->getData();
			
			
			int smallest = (int)a.length();
			if ((int)b.length() < smallest)
			{
				smallest = b.length();
			}
			
			int i;
			for (i = 0; i < smallest; i++)
			{
				if ((int)a[i] != (int)b[i])
				{
					break;
				}
			}
			if (i == smallest)
			{
				continue;
			}
			if ((int)a[i] > (int)b[i])
			{
				swap(current, current->getNext());
				
				if (current == head)
				{
					head = current->getPrev();
				}
				restart = true;
				jumpToHead();
				
			}
		//}
		/*
		jumpToHead();
		movingHead = true;
		while (moveNext() == 0)
		{
			cout << "here";
			movePrev();
			a = *getCurrent();
			temp = current;
			moveNext();
			b = *getCurrent();
		
			index = 0;
			while (int(a[index]) == int(b[index]))
			{
				cout << "beans";
				index++;
				if ((index > a.length()) || (index > b.length()))
				{
					break;
				}
			}
			cout << index;
			if ((index > a.length()) || (index > b.length()))
			{
				//The words are the same, no need to swap them
				movingHead = false;
				//cout << "Continuing";
				continue;
			}
			
			cout << "\n" << int(a[index]) << " ";
			cout << int(b[index]) << endl;
			
			if (int(b[index]) < int(a[index]))
			{
				cout << "Swapping";
				swap(temp, current);
				if (movingHead)
				{
					head = current;
					movingHead = false;
				}
				//current = temp;
			}
			else
			{				
				//moveNext();
			}
			
			if (movingHead)
			{
				movingHead = false;
			}
		}*/
	}
	//temp = NULL;
}

int LinkedList::jumpToHead()
{
	current = head;
	if (current == NULL)
	{
		return -1;
	}
	return 0;
}

int LinkedList::jumpToTail()
{
	current = tail;
	if (current == NULL)
	{
		return -1;
	}
	return 0;
}

int LinkedList::moveNext()
{
	//cout << "Next";
	current = current->getNext();
	if (current == NULL)
	{
		return -1;
	}
	return 0;
}

int LinkedList::movePrev()
{
	//cout << "Prev";
	current = current->getPrev();
	if (current == NULL)
	{
		return -1;
	}
	return 0;
}

value_type* LinkedList::getCurrent() const
{
	return current->getData();
}

void LinkedList::operator += (LinkedList& other)
{
	if (other.jumpToHead() == -1)
	{
		return;
	}
	do
	{
		value_type* temp = new value_type(*other.getCurrent());
		addToTail(temp);
	}
	while (other.moveNext() == 0);
}


ostream& operator << (ostream& out, LinkedList& temp)
{
	if (temp.jumpToHead() == -1)
	{
		out << "List is empty";
		return out;
	}
	do
	{
		out << *temp.getCurrent() << " ";
	}
	while (temp.moveNext() == 0);
	return out;
}

void LinkedList::swap(Node* a, Node* b)
{
	a->setNext(b->getNext());
	b->setNext(a);
	if (a->getNext() != NULL)
	{
		a->getNext()->setPrev(a);
	}
	
	b->setPrev(a->getPrev());
	a->setPrev(b);
	if (b->getPrev() != NULL)
	{
		b->getPrev()->setNext(b);
	}
}



















































