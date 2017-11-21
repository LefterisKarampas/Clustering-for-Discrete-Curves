#ifndef _NODE_H_
#define _NODE_H_

#include <iostream>
#include "Types.h"
using namespace std;


class Node{
private:
	Curve * value;
	Node * next;
public:
	Node(Curve * x);
	~Node();
	int Set_next(Node * next);
	Node * GetNext();
	Curve * GetValue();
	void Clear_up();
	void Search_Clear();
};


#endif