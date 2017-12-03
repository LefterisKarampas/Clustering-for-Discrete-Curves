#ifndef LSH_CURVE_H_
#define LSH_CURVE_H_

#include "Grid.h"
#include "HashTable.h"
#include "List.h"
#include "Types.h"
#include <vector>
#include <iostream>

class LSH_Curve{
private:
	Grid** G;						//Array of Grids
	HashTable *HT;					//LSH HashTAble
	int k;								//Pointumber of k Grids
	int id;								//LSH id number
public:
	LSH_Curve(int,int,int,int,int,int,int(*hash_function)(const Point &,const std::vector<int> &,int,int,std::vector<double> **,double *));
	~LSH_Curve();
	Point * Create_GridCurve(const T_Curve &);
	int LSH_Insert(int);
	void LSH_RangeSearch(int ,T_Curve & ,std::vector<int> *,
	std::vector<double> *,long double (*distance)( T_Curve&, T_Curve &));
	void LSH_RangeSearch(int ,T_Curve & ,std::vector<int> *,
		long double (*distance)( T_Curve&, T_Curve &));
	//List * LSH_Search(T_Curve *,char *,bool *);
	//Curve * Check_all(T_Curve *,char *,Curve * ,long double *,bool *,double,std::vector<char *> *,Curve *,long double *,long double (*distance)(const T_Curve &,const T_Curve &));
};


#endif