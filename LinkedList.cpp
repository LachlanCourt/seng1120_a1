/*************************************
**** Lachlan Court
**** c3308061
**** 13/09/2020
**** SENG1120 Assignment 1
**************************************/


//cd /cygdrive/C/Users/lachl/OneDrive/Documents/Uni/SENG1120_Assessment/Assignment1

#include <iostream>
using namespace std;
#include "LinkedList.h"
typedef Node::value_type value_type;

// Constructor, initialise empty list
LinkedList::LinkedList()
{
	head = NULL;
	tail = NULL;
	current = NULL;
	size = 0;
}

// Deconstructor
LinkedList::~LinkedList()
{
	// Loop through until the head is not NULL and delete the head each time
	while (head != NULL)
	{	
		// Keep track of the item in the list after the head
		current = head->getNext();
		// Delete head
		delete(head);
		// Set the head to what used to be the second item in the list
		head = current;
	}
}

// Query the size of the list
int LinkedList::getSize() const
{
	return size;
}

// Receives a string and adds the elements to the Linked List delimetered by spaces
void LinkedList::add(value_type data)
{
	// Declare a temp string which will hold the value of the string iterated so far
	value_type* temp = new value_type();
	// Loop through the parsed data one character at a time
	for (long unsigned int i = 0; i < data.length(); i++)
	{
		// If the charater is a space, the word will be added to the list
		if (data[i] == ' ')
		{
			addToTail(temp);
			// Reset temp ready for a new word
			temp = new value_type();
		}
		else
		{
			// If the character is not a space, add the character to temp
			*temp += data[i];
		}
	}
	// The last word doesn't end in a space, so it needs to be added explicitly
	if (temp->length() != 0)
	{
		addToTail(temp);
	}
}

// Receives a string that will be added to the Linked List at the end
void LinkedList::addToTail(value_type* data_)
{
	// Check if the list is empty
	if ((head == NULL) && (tail == NULL))
	{
		// Create a new node with the specified data
		head = new Node(data_);
		// The list has one item so the tail and head are the same node
		tail = head;
		// Increase the size of the list
		size++;
	}
	else
	{
		// Create a new node with the specified data
		current = new Node(data_);
		// Link the new node's previous to the tail of the list
		current->setPrev(tail);
		// Link the tail's next to the new node
		tail->setNext(current);
		// Set the tail to the new node
		tail = current;
		// Having just manipulated the current, reset it to head
		jumpToHead();
		// Increase the size of the list
		size++;
	}
}

// Receives a string that will be added to the Linked List at the start
void LinkedList::addToHead(value_type* data_)
{
	// Check if the list is empty
	if ((head == NULL) && (tail == NULL))
	{
		// Create a new node with the specified data
		tail = new Node(data_);
		// The list has one item so the tail and head are the same node
		head = tail;
		// Increase the size of the list
		size++;
	}
	else
	{
		// Create a new node with the specified data
		current = new Node(data_);
		// Link the new node's next to the head of the list
		current->setNext(head);
		// Link the head's previous to the new node
		head->setPrev(current);
		// Set the head to the new node
		head = current;
		// Increase the size of the list
		size++;
	}
}

// Receives a string that will be removed from the Linked List
void LinkedList::remove(value_type identifier)
{
	// Check if the list is empty and return
	if ((head == NULL) && (tail == NULL))
	{
		return;
	}
	
	// Create a new Linked List and add the identifier into the list. A multi word identifier will be added as separate Nodes
	LinkedList temp = LinkedList();
	temp.add(identifier);
	// Check if the temp List is empty
	if (temp.jumpToHead() == -1)
	{
		return;
	}
	// Define a value to keep track of whether the identifier has been found in the Linked List
	bool identified = false;
	// After a deletion, the loop will be restarted
	bool restart = false;
	// Loop through the Linked List
	for (jumpToHead(); current != NULL; moveNext())
	{
		// If a deletion occured last iteration, reset the current to the head
		if (restart)
		{
			restart = false;
			jumpToHead();
		}
		// Check if the current of the temp list matches the current of the main Linked List
		if (*temp.getCurrent() == *getCurrent())
		{
			// If it matches, move to the next item in the list, and check if the temp list's current has reached the tail
			if (temp.moveNext() == -1)
			{	
				// The entire temp list is inside the main list so confirm by setting identified to True
				identified = true;
				// Walk back through the main Linked List to get to the start of the temp list occurrence
				for (int i = 1; i < temp.getSize(); i++)
				{
					movePrev();
				}
				// Declare a new Node to keep track of where the deletion is occuring in the main list because removeCurrent resets current pointer to head
				Node* newStart;
				// Loop through the length of the temp list to delete each word
				for (int i = 0; i < temp.getSize(); i++)
				{
					// If the phrase to be deleted is not at the start of the List
					if (current->getPrev() != NULL)
					{
						// Set newStart to the Node just before the one that will be deleted
						newStart = current->getPrev();
						// Delete the current Node
						deleteCurrent();
						// If the Node that was deleted is not at the end of the Linked List, reset the current. If it was at the end, then that was the last occurence and the function is about to end
						if (newStart->getNext() != NULL)
						{
							// Reset the current to the next of it's old previous to get to the new next item in the list
							current = newStart->getNext();
						}
					}
					// If the phrase to be deleted is at the start of the list
					else
					{
						// deleteCurrent() already sets the current back to head so no need to shuffle
						deleteCurrent();
					}
				}
				// Reset temp's current to head in case there are multiple occurences of the phrase in the main Linked List
				temp.jumpToHead();
				// Ensure that current is reset at the start of the for loop as the for loop immediately goes to next
				restart = true;
			}
		}
	}
	
	// If no item was found, return
	if (!identified)
	{
		//cout << "No such item in list\n";
		return;
	}
}

// Receives a string and counts how many occurrences of that string are in the Linked List
int LinkedList::count(const value_type identifier)
{
	int occurrences = 0;
	// jumpToHead returns -1 if the Linked list is empty
	if (jumpToHead() == -1)
	{
		return -1;
	}
	// Loop through the Linked List
	for (jumpToHead(); current != NULL; moveNext())
	{
		// Check if the identifier is the value of the current position in the Linked List
		if (identifier == *getCurrent())
		{
			// Increment the counter
			occurrences++;
		}
	}
	// Reset the current to head as it has just been manipulated
	jumpToHead();
	// Return the number of occurrences
	return occurrences;
}

// Sorts the Linked List in alphabetical order
void LinkedList::sort()
{
	// Two Nodes will be picked out at a time to be checked
	value_type a;
	value_type b;
	// After a swap, the loop will be restarted
	bool restart = false;
	
	// Check if the Linked List is empty
	if ((head == NULL) && (tail == NULL))
	{
		return;
	}

	// Loop through the Linked List
	for (jumpToHead(); current->getNext() != NULL; moveNext())
	{
		// If a swap occured last iteration, reset the current to the head
		if (restart)
		{
			jumpToHead();
			restart = false;
		}
		
		// Pick out the data from two nodes to compare
		a = *current->getData();
		b = *current->getNext()->getData();
		
		// Determine which of the two words is shorter
		int smallest = (int)a.length();
		if ((int)b.length() < smallest)
		{
			smallest = b.length();
		}
		
		// Loop through the length of the smaller word
		int i;
		for (i = 0; i < smallest; i++)
		{
			// Keep checking until a character that is unique in the two words is found
			if ((int)a[i] != (int)b[i])
			{
				break;
			}
		}
		// If the for loop above has reached the length of the smallest word, a swap is not necessary as they are the same (Or the larger word starts with the smaller word)
		if (i == smallest)
		{
			continue;
		}
		// Now that a unique character has been found, determine if a swap is necessary by comparing ASCII codes
		if ((int)a[i] > (int)b[i])
		{
			// Swap the two nodes
			swap(current, current->getNext());
			
			// If the first word has been swapped, reset the head
			if (current == head)
			{
				head = current->getPrev();
			}
			// Ensure that current is reset at the start of the for loop
			restart = true;
			// Reset current now as well, in case current is currently NULL
			jumpToHead();
		}
	}
	// As current has been manipulated, ensure it is reset to the head
	jumpToHead();
}

// Resets current to head
int LinkedList::jumpToHead()
{
	current = head;
	// Return -1 if current is now NULL - indicating list is empty
	if (current == NULL)
	{
		return -1;
	}
	return 0;
}

// Resets current to tail
int LinkedList::jumpToTail()
{
	current = tail;
	// Return -1 if current is now NULL - indicating list is empty
	if (current == NULL)
	{
		return -1;
	}
	return 0;
}

// Moves current to the next Node in the list
int LinkedList::moveNext()
{
	current = current->getNext();
	// Return -1 if current is now NULL - reached the end of the list
	if (current == NULL)
	{
		return -1;
	}
	return 0;
}

// Moves current to the previous Node in the list
int LinkedList::movePrev()
{
	current = current->getPrev();
	// Return -1 if current is now NULL - reached the start of the list
	if (current == NULL)
	{
		return -1;
	}
	return 0;
}

// Return the data stored in the current Node
value_type* LinkedList::getCurrent() const
{
	return current->getData();
}

// Add the otherList data onto the existing Linked List
void LinkedList::operator += (LinkedList& otherList)
{
	// Check if otherList is empty and also move otherList's current to head
	if (otherList.jumpToHead() == -1)
	{
		return;
	}
	// Loop through otherList
	do
	{
		// Create a new string with the same value as the Node in otherList
		value_type* temp = new value_type(*otherList.getCurrent());
		// Add new string to the existing Linked List
		addToTail(temp);
	}
	// Loop until the end of otherList is reached
	while (otherList.moveNext() == 0);
}

// Output the Linked List as a sentence
ostream& operator << (ostream& out, LinkedList& temp)
{
	// Set current to head, return if the Linked List is empty
	if (temp.jumpToHead() == -1)
	{
		out << "List is empty";
		return out;
	}
	// Loop through the list
	do
	{
		// Output the data of the current Node followed by a space
		out << *temp.getCurrent() << " ";
	}
	// Keep looping until the end of the loop is reached
	while (temp.moveNext() == 0);
	// As current has been manipulated, reset it to head
	temp.jumpToHead();
	return out;
}

// Swap two Nodes in a Linked List
void LinkedList::swap(Node* a, Node* b)
{	
	// Set the next of the first Node to the next of the second Node
	a->setNext(b->getNext());
	// Set the next of the second Node to the first Node
	b->setNext(a);
	// Set the first Node's next's previous to the first Node
	if (a->getNext() != NULL)
	{
		a->getNext()->setPrev(a);
	}
	
	// Set the previous of the second Node to the previous of the first Node
	b->setPrev(a->getPrev());
	// Set the previous of the first Node to the second Node
	a->setPrev(b);
	// Set the second Node's previous's Next to the Second Node
	if (b->getPrev() != NULL)
	{
		b->getPrev()->setNext(b);
	}
}


void LinkedList::deleteCurrent()
{
			// If there is one item in the list
			if (head == tail)
			{
				// Reset the head and tail as the list is about to become empty
				head = NULL;
				tail = NULL;
			}
			// If the first item in the list
			else if (current == head)
			{
				// Set the head to the second item in the list as the first is about to be removed
				head = current->getNext();
				head->setPrev(NULL);
		
			}
			// If the last item in the list
			else if (current == tail)
			{
				// Set the tail to the second last item in the list as the last is about to be removed
				tail = current->getPrev();
				tail->setNext(NULL);
		
			}
			// The list has more than one item and the item to be removed is not at the head or tail
			else
			{
				// Link the node before the current to the node after the current
				current->getPrev()->setNext(current->getNext());
				current->getNext()->setPrev(current->getPrev());
			}
			// Delete the current and decrement the size
			delete(current);
			size--;
			// current has just been deleted so reset it to the head and start the loop over
			jumpToHead();
}
















































