#include <iostream>
using namespace std;
#ifndef NODE_CLASS
#define NODE_CLASS
#include "Account.h"
class Node
{
	public:
		typedef Account value_type;
	
		Node();
		Node(Node* p = NULL, Node* n = NULL, value_type* i = new value_type());
		Node(value_type* i = new value_type());
		~Node();
	
		void setNext(Node* n_);
		void setPrev(Node* p_);
		
		Node* getNext() const;
		Node* getPrev() const;
		
		value_type* getData();
		void setData(value_type* data_);
		
	private:
		value_type* data;
		Node* next;
		Node* prev;
	
};

#endif