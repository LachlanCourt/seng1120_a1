#include <iostream>
using namespace std;
#ifndef NODE_CLASS
#define NODE_CLASS
#include <string>

class Node
{
	public:
		typedef string value_type;
		Node();
		Node(Node* p, Node* n, value_type* i);
		Node(value_type* i);
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