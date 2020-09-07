#include <iostream>
using namespace std;
#include "Node.h"
typedef string value_type;

Node::Node()
{
	next = NULL;
	prev = NULL;
}
		
Node::Node(Node* p, Node* n, value_type* i)
{
	next = n;
	prev = p;
	data = i;
}

Node::Node(value_type* i)
{
	next = NULL;
	prev = NULL;
	data = i;
}

Node::~Node()
{
	delete(data);
}
	
void Node::setNext(Node* n_)
{
	next = n_;
}

void Node::setPrev(Node* p_)
{
	prev = p_;
}
		
Node* Node::getNext() const
{
	return next;
}
Node* Node::getPrev() const
{
	return prev;
}

value_type* Node::getData()
{
	return data;
}
void Node::setData(value_type* data_)
{
	data = data_;
}


