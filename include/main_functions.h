#ifndef _MAIN_FUNC_H_
#define _MAIN_FUNC_H_

#include "Curve_Info.h"
#include "LSH_Curve.h"
#include <iostream>
#include <fstream>

int get_args(int ,char ** , char ** , char **, char **,char **);

int read_config(char *,int *,int *,int *);

LSH_Curve ** read_curves(char *,int,int,Curve_Info ***,int *);

void Print_Results(std::ofstream& myfile,Clusters * clusters);

void Clustering(char * ,int ,int ,LSH_Curve ** ,int ,long double (*distance)(T_Curve &,T_Curve &),int);

#endif //_MAIN_FUNC_H_
