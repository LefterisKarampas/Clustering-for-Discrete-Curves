#ifndef _MAIN_FUNC_H_
#define _MAIN_FUNC_H_

#include "Curve_Info.h"
#include "Types.h"

int get_args(int ,char ** , char ** , char **, char **,char **);

int read_config(char *,int *,int *,int *);

int read_curves(char *,int,int,Curve_Info<T_Curve> **);


#endif //_MAIN_FUNC_H_
