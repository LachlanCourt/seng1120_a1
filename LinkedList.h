#include <iostream>
using namespace std;
#ifndef LACHLAN_LINKEDLIST
#define LACHLAN_LINKEDLIST
#include "Node.h"

class LinkedList
{
	
	public:
		typedef Node::value_type value_type;
		LinkedList();
		~LinkedList();
		int getSize() const;
		void add(const char* data_);
		void addToTail(value_type* data_);
		void addToHead(value_type* data_);
		void remove(const string identifier);
		
		int jumpToHead();
		int jumpToTail();
		int moveNext();
		int movePrev();
		value_type* getCurrent() const;
		
		void operator += (LinkedList& temp);
	
	private:
		Node* head;
		Node* tail;
		Node* current;
		int size;
		
};

ostream& operator << (ostream& out, LinkedList& temp);
#endif