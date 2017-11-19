#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <vector>
#include "../include/main_functions.h"
#include "../include/Curve.h"
#include "../include/Curve_Info.h"
#include "../include/Distance.h"
#include "../include/Types.h"


using namespace std;

template class Curve<T_Curve,T_GridCurve>;						//Initialize the template class for Curve
template class Curve_Info<T_Curve>;


int main(int argc,char **argv){
	char * input_file = NULL;
	char * config_file = NULL;
	char * output_file = NULL;
	char * metric = NULL;
	int num_clusters,num_grid,num_HT;
	//Read command line args
	if(get_args(argc,argv,&input_file,&config_file,&output_file,&metric)){
		cerr << "Fail read args" << endl;
		exit(1);
	}
	//Read configuration file
	if(read_config(config_file,&num_clusters,&num_grid,&num_HT)){
		cerr << "Fail read configuration file" << endl;
		exit(2);
	}
	//Read curves from file
	Curve_Info<T_Curve> * curve_info = NULL;
	if(read_curves(input_file,num_HT,num_grid,&curve_info)){
		cerr << "Failed read input file" << endl;
		exit(3);
	}


	//Free the allocate space for arguments
	free(input_file);
	free(config_file);
	free(output_file);
	free(metric);
	return 0;
}