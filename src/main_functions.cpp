#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string.h>
#include <stdio.h>
#include "../include/Curve_Info.h"
#include "../include/Types.h"

using namespace std;


//Get the command line args
int get_args(int argc,char ** argv, char ** input_file, char **config_file, char **output_file,char **metric){
	int i;
	int count = 0;
	for(i=1;i<argc;i+=2){
		//Help manual
		if(!strcmp(argv[i],"-h")){
			fprintf(stderr,"Usage: %s -i <input_file> -c <configuration_file> -o <output_file> -d <metric>\n",argv[0]);
			exit(1);
		}
		//Input file argument
		else if(!strcmp(argv[i],"-i")){
			if((i+1) < argc && (*input_file) == NULL){
				(*input_file) = (char *)malloc(sizeof(char) * (strlen(argv[i+1])+1));
				strcpy(*input_file,argv[i+1]);
				count++;
			}
			else{
				return 1;
			}
		}
		//Config file argument
		else if(!strcmp(argv[i],"-c")){
			if((i+1) < argc && (*config_file) == NULL){
				(*config_file) = (char *)malloc(sizeof(char) * (strlen(argv[i+1])+1));
				strcpy(*config_file,argv[i+1]);
				count++;
			}
			else{
				return 1;
			}
		}
		//Output file argument
		else if(!strcmp(argv[i],"-o")){
			if((i+1) < argc && (*output_file) == NULL){
				(*output_file) = (char *)malloc(sizeof(char) * (strlen(argv[i+1])+1));
				strcpy(*output_file,argv[i+1]);
				count++;
			}
			else{
				return 1;
			}
		}
		//Metric argument
		else if(!strcmp(argv[i],"-d")){
			if((!strcmp(argv[i+1],"Frechet")) || (!strcmp(argv[i+1],"DTW"))){
				(*metric) = (char *)malloc(sizeof(char) * (strlen(argv[i+1])+1));
				strcpy(*metric,argv[i+1]);
				count++;
			}
			else{
				cerr << "Metric parameter in {Frechet,DTW}" << endl;
				return 1;
			}
		}
		else{
			return 1;
		}
	}
	//If all arguments were not given, print error message and exit
	if(count != 4){
		fprintf(stderr,"Usage: %s -i <input_file> -c <configuration_file> -o <output_file> -d <metric>\n",argv[0]);
		return 1;
	}
	return 0;
}



//Read the config parameters from file
int read_config(char * config_file,int *num_clusters,int *num_grid,int *num_HT){
	*num_grid = 2;
	*num_HT = 3;
	string line;
	ifstream myfile(config_file);
	if (myfile.is_open())
	{
		while ( getline (myfile,line) )
		{
			char * temp = (char *) malloc(sizeof(char) * (line.size()+1));
			strcpy(temp,line.c_str());
			char *p = strtok(temp, " ");
			if(!strcmp(p,"number_of_clusters:")){
			 	p = strtok(NULL," ");
			 	if(p != NULL){
			 		*num_clusters = atoi(p);
			 	}
			 	else{
			 		myfile.close();
			 		return 1;
			 	}
			 }
			else if(!strcmp(p,"number_of_grid_curves:")){
			 	p = strtok(NULL," ");
			 	if(p != NULL){
			 		*num_grid = atoi(p);
			 	}
			 	else{
			 		myfile.close();
			 		return 1;
			 	}
			}
			else if(!strcmp(p,"number_of_hash_tables:")){
				p = strtok(NULL," ");
				if(p != NULL){
					*num_HT = atoi(p);
				}
				else{
					myfile.close();
					return 1;
				}
			}
			else{
			 	myfile.close();
			 	return 1;
			}
			free(temp);
		}
		myfile.close();
	}
	else{ 
		cout << "Unable to open file";
		return 1;
	} 
return 0;
}


int read_curves(char *input_file,int num_HT,int num_grid,Curve_Info<T_Curve> ** curve_info){

	return 0;
}