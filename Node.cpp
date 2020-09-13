/*************************************
**** Lachlan Court
**** c3308061
**** 13/09/2020
**** SENG1120 Assignment 1
**************************************/

#include <iostream>
using namespace std;
#include "Node.h"
typedef string value_type;

// Default Constructor
Node::Node()
{
	next = NULL;
	prev = NULL;
	data = new value_type();
}

// Initilise node with existing next and previous and data
Node::Node(Node* p, Node* n, value_type* i)
{
	next = n;
	prev = p;
	data = i;
}

// Initialise node with only data and NULL directional pointers that can be assigned later
Node::Node(value_type* i)
{
	next = NULL;
	prev = NULL;
	data = i;
}

// The pointers to other Nodes need to remain so only delete the Data
Node::~Node()
{
	delete(data);
}

// Set the next pointer for the Node
void Node::setNext(Node* n_)
{
	next = n_;
}

// Set the previous pointer for the Node
void Node::setPrev(Node* p_)
{
	prev = p_;
}

// Set the data pointer for the Node
void Node::setData(value_type* data_)
{
	data = data_;
}

// Query the next pointer for the Node
Node* Node::getNext() const
{
	return next;
}

// Query the previous pointer for the Node
Node* Node::getPrev() const
{
	return prev;
}

// Query the data pointer for the Node
value_type* Node::getData()
{
	return data;
}



