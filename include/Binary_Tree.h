#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_
#include "../include/Types.h"
#include "../include/Cluster.h"


template <typename object>
class Node{
	object *value;
	Node<object> * left;
	Node<object> * right;
public:
	Node(object *);
	~Node();
	object * Node_Get_value();
	Node * Node_Get_left();
	Node * Node_Get_right();
};

template <typename object>
class Binary_Tree{
	Node<object> * root;
public:
	Binary_Tree();
	~Binary_Tree();
	object * Binary_Tree_Mean_Frechet(Neighbors);
};


#endif