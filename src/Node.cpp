#include <iostream>
#include <vector>
#include "../include/Node.h"

//---------------------------Node Functions------------------------------
//

Node::Node(Curve * x):value(x){
	this->next = NULL;
}




Node::~Node(){
	if(this->value != NULL)
		delete this->value;
	if(this->next != NULL){
		delete this->next;
	}
}




int Node::Set_next(Node * next){
	this->next = next;
	return 0;
}





Node * Node::GetNext(){
	return this->next;
}




Curve * Node::GetValue(){
	return this->value;
}




void Node::Clear_up(){
	this->value->Clear_up();
}




void Node::Search_Clear(){
	this->value = NULL;
}
