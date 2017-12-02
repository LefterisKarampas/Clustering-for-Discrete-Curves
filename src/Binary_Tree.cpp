#include "../include/Binary_Tree.h"
#include <cstdlib>
#include <iostream>
#include <cmath>

using namespace std;

template <typename object>
Node<object>::Node(object * value){
	this->value = value;
	this->left = NULL;
	this->right = NULL;
}

template <typename object>
Node<object>::~Node(){
	if(this->left != NULL){
		delete this->left;
	}
	if(this->right != NULL){
		delete this->right;
	}
}

template <typename object>
object * Node<object>::Node_Get_value(){
	return this->value;
}

template <typename object>
Node<object> * Node<object>::Node_Get_left(){
	return this->left;
}

template <typename object>
Node<object> * Node<object>::Node_Get_right(){
	return this->right;
}

template <typename object>
Node<object> * Node<object>::PostOrder(int h,int max_h,Neighbors neigh){
	if(h == max_h){
		value = 
	}
}




//--------------------Binary_Tree--------------------//

template <typename object>
Binary_Tree<object>::Binary_Tree(){
	this->root = NULL;
}

template <typename object>
Binary_Tree<object>::~Binary_Tree(){
	if(this->root != NULL){
		delete this->root;
	}
}



template <typename object>
object * Binary_Tree<object>::Binary_Tree_Mean_Frechet(Neighbors neigh){
	int h = 0;
	int max_h = int((float)log2(neigh.size()) + 0.5);
	//this->root->PostOrder(h,max_h);
	return this->root->Node_Get_value();
}






