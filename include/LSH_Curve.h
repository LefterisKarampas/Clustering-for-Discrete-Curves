#ifndef LSH_CURVE_H_
#define LSH_CURVE_H_

#include "Grid.h"
#include "HashTable.h"
#include "List.h"
#include "Types.h"

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
	//List * LSH_Search(T_Curve *,char *,bool *);
	//Curve * Check_all(T_Curve *,char *,Curve * ,long double *,bool *,double,std::vector<char *> *,Curve *,long double *,long double (*distance)(const T_Curve &,const T_Curve &));
};


#endif