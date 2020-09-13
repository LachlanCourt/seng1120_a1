/*************************************
**** Lachlan Court
**** c3308061
**** 13/09/2020
**** SENG1120 Assignment 1
**************************************/

#include <iostream>
using namespace std;
#ifndef NODE_CLASS
#define NODE_CLASS
#include <string>

class Node
{
	public:
		typedef string value_type;
		
		//Constructors	
		Node();
		Node(Node* p, Node* n, value_type* i);
		Node(value_type* i);
		//Destructor
		~Node();
		
		//****Queries****//
		
		//precondition: None
		//postcondition: Function returns the pointer to the next Node object
		Node* getNext() const;
		//precondition: None
		//postcondition: Function returns the pointer to the previous Node object
		Node* getPrev() const;
		//precondition: Data should not be NULL
		//postcondition: Function returns the pointer to the data
		value_type* getData();
		
		//****Data manipulation****//
	
		//precondition: None
		//postcondition: Node's next variable will be a pointer to the next Node object
		void setNext(Node* n_);
		//precondition: None
		//postcondition: Node's previous variable will be a pointer to the next Node object
		void setPrev(Node* p_);
		//precondition: None
		//postcondition: Node's data variable will be a pointer to data on the heap
		void setData(value_type* data_);
		
	private:
		//****Instance variables****//
		value_type* data;
		Node* next;
		Node* prev;
};

#endif