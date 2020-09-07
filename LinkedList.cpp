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

void LinkedList::add(const char* data_)
{
	value_type data = data_;
	value_type* temp = new value_type("");
	for (long unsigned int i = 0; i < data.length(); i++)
	{
		if (data[i] == ' ')
		{
			addToTail(temp);
			temp = new value_type("");
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

void LinkedList::remove(string identifier)
{
	if ((head == NULL) && (tail == NULL))
	{
		return;
	}
	
	jumpToHead();
	bool identified = false;
	do
	{
		/*
		if (identifier.compare(current->getData()) == 0)
		{
			identified = true;
			break;
		}*/
	}
	while (moveNext() == 0);
	
	if (!identified)
	{
		cout << "No such item in list" << endl;
		return;
	}
	
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
	current = current->getNext();
	if (current == NULL)
	{
		return -1;
	}
	return 0;
}

int LinkedList::movePrev()
{
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

void LinkedList::operator += (LinkedList& temp)
{
	if (temp.jumpToHead() == -1)
	{
		return;
	}
	do
	{
		addToTail(temp.getCurrent());
	}
	while (temp.moveNext() == 0);
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





















































