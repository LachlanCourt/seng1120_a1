/*************************************
**** Lachlan Court
**** c3308061
**** 13/09/2020
**** SENG1120 Assignment 1
**************************************/

#include <iostream>
using namespace std;
#ifndef LINKEDLIST_CLASS
#define LINKEDLIST_CLASS
#include "Node.h"

class LinkedList
{
	
	public:
		typedef Node::value_type value_type;
		
		//Constructor
		LinkedList();
		//Destructor
		~LinkedList();
		
		//****Queries****//
		
		//precondition: None
		//postcondition: Function returns the size of the Linked List
		int getSize() const;
		//precondition: None (Empty list possibility is checked during function)
		//postcondition: Function returns the number of occurrences of the specified identifier
		int count(const value_type identifier);
		
		//****Data manipulation****//
		
		//precondition: None
		//postcondition: The data is stored in the list having been split up into individual words with space delimeter
		void add(const value_type data);
		//precondition: None (Empty list possibility is checked during function)
		//postcondition: Linked List has data added as a new node at the end of the list
		void addToTail(value_type* data_);
		//precondition: None (Empty list possibility is checked during function)
		//postcondition: Linked List has data added as a new node at the start of the list
		void addToHead(value_type* data_);
		//precondition: identifier cannot be NULL but can be empty
		//postcondition: All items that match the specified identifier will be removed from the list
		void remove(const value_type identifier);
		//precondition: None (Empty list possibility is checked during function)
		//postcondition: Linked list will be sorted by alphabetical order
		void sort();
		
		//****List traversing****//
		
		//precondition: None
		//postcondition: Linked List current is set to head, returns -1 if list is empty and 0 if successful
		int jumpToHead();
		//precondition: None
		//postcondition: Linked List current is set to tail, returns -1 if list is empty and 0 if successful
		int jumpToTail();
		//precondition: Linked List current cannot be NULL
		//postcondition: Linked List current is set to the value of it's next, returns -1 if current is now NULL and 0 if successful
		int moveNext();
		//precondition: Linked List current cannot be NULL
		//postcondition: Linked List current is set to the value of it's previous, returns -1 if current is now NULL and 0 if successful
		int movePrev();
		//precondition: Linked List current cannot be NULL
		//postcondition: Returns the pointer to the data of the current Node
		value_type* getCurrent() const;
		
		//precondition: temp cannot be NULL but the Linked List itself can be empty
		//postcondition: Adds the items in the temp Linked List onto the end of the existing Linked List
		void operator += (LinkedList& otherList);
	
	private:
		//****Instance variables****//
		Node* head;
		Node* tail;
		Node* current;
		int size;
		
		//****Private methods****//
		
		//precondition: Neither argument can be NULL
		//postcondition: The Nodes will be swapped in the Linked List by manipulating the next and previous values
		void swap(Node* a, Node* b);

		void deleteCurrent();
};

//precondition: temp cannot be NULL but the Linked List itself can be empty
//postcondition: The contents of the Linked List will be printed out, or "List is Empty" if temp is empty
ostream& operator << (ostream& out, LinkedList& temp);
#endif