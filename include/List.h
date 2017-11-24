#ifndef _LIST_H_
#define _LIST_H_

#include <iostream>
#include <vector>
#include "Node.h"
#include "Types.h"

using namespace std;

class List{
private:
	Node * head;
	int count;
public:
	List();
	~List();
	int List_Insert(int,Point *);
	//List * List_Search(Curve *,bool *);
	//void Clear_up();
	void Set_NULL();
	//void Search_Clear();
	/*Curve * find_min(Curve ,long double *,
			long double (*distance)(const  std::vector< std::vector<double> > &,const std::vector< std::vector<double> > &),double,std::vector<char *> *);
	Curve * find_min(Curve ,long double *,
			long double (*distance)(const  std::vector< std::vector<double> > &,const std::vector< std::vector<double> > &));
	Curve * find_nearest_min(Curve *,Curve *,long double *,bool *,double ,std::vector<char *> *,Curve *,long double *,long double(*distance)(const std::vector< std::vector<double> >&,const std::vector< std::vector<double> >&));
	Curve * find_nearest(Curve *,Curve *,long double *,long double(*distance)(const std::vector< std::vector<double> >&,const std::vector< std::vector<double> >&));
	*/
};



#endif