#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string.h>
#include <stdio.h>
#include "../include/Curve_Info.h"
#include "../include/Types.h"
#include "../include/LSH_Curve.h"
#include "../include/HashFunctions.h"

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

int Get_num_lines(char *input_file){
	char * command;
	int n;
	char buff[32];
	command = (char *) malloc(strlen(input_file)+strlen("wc -l  | cut -d ' ' -f1")+2);
	sprintf(command, "wc -l %s | cut -d ' ' -f1",input_file);
	FILE *in;
	if(!(in = popen(command, "r"))){
		exit(1);
	}
	n = 100;
	while(fgets(buff, sizeof(buff), in)!=NULL){
		n = atoi(buff);
	}
	pclose(in);
	free(command);
	return n;
}


LSH_Curve ** read_curves(char *input_file,int num_HT,int num_grid,Curve_Info *** curve_info,int *n){
	string line;
	ifstream myfile(input_file);
	if (!myfile.is_open())
	{
		cerr << "OPEN" << endl;
		return NULL;
	}
	//Count the lines of the file (get the number of curves)
	*n = Get_num_lines(input_file);

	//Initialize the curve_info structure
	*curve_info = new Curve_Info*[*n];
	int array_index = 0;

	int dim = 2;
	int dim_flag = 0;
	int count = 0;
	LSH_Curve **LSH = new LSH_Curve*[num_HT];
	//Read the lines and split the info
	while ( getline (myfile,line) ){
		const char * temp = line.c_str();
		std::vector<string> splitted;
		int len = strlen(temp);
		int j=0;
		int flag = 0;
		int index = 0;
		//Split the line
		while(j<=len){
			//If find tab or comma out of () then cut field
			if(temp[j] == '\t' || (flag == 0 && temp[j] == ',')){
				splitted.push_back(line.substr(index,j-index));
				if(temp[j] == ' '){
					j +=2;
				}
				else{
					j++;
				}
				index = j;
				continue;
			}
			else if(temp[j] == '(' || temp[j] == ')'){
				flag = (flag +1) % 2;
			}
			j++;
		}
		splitted.push_back(line.substr(index,j-index-1));
		Curve_Info * new_curve;
		T_Curve * curve_points;
		for(unsigned int i =0;i<splitted.size();i++){
			//Get the dimension if exists in file
			if(!count && dim_flag == 0 && splitted[0] == "@dimension"){
				dim = atoi(splitted[1].c_str());
				dim_flag = 1;
				break;
			}
			//Otherwise get the curve's info
			switch(i){
				case 0:{
					curve_points = new T_Curve();
					break;
				}
				case 1:{
					int points = atoi(splitted[i].c_str());
					int k_points = splitted.size() - 2;
					if(points != k_points){
						fprintf(stderr,"Error Message: Line %d - CurveID: %s\n\tExpected curve with %d points and get curve with %d points\n",\
						count+1,splitted[0].c_str(),points,k_points);
						return NULL;
					}
					break;
				}
				default:{
					Point p;
					temp = splitted[i].c_str();
					double x[dim];
					//Depending on the dimension read d-dimension point
					if(dim == 2){
						if(sscanf(temp," (%lf, %lf)",x,x+1) != dim){
							cerr << "We expected " <<dim<<"-dimensional curve"<<endl;
							cerr << temp << endl;
							exit(1);
						}
					}
					else if(dim == 3){
						if(sscanf(temp," (%lf, %lf, %lf)",x,x+1,x+2) != dim){
							cerr << "We expected " <<dim<<"-dimensional curve"<<endl;
							cerr << temp << endl;
							exit(1);
						}
					}
					else{
						if(sscanf(temp," (%lf, %lf, %lf, %lf)",x,x+1,x+2,x+3) != dim){
							cerr << "We expected " <<dim<<"-dimensional curve"<<endl;
							cerr << temp << endl;
							exit(1);
						}
					}
					for(j=0;j<dim;j++){
						p.push_back(x[j]);
					}
					curve_points->push_back(p);

				}
			}
		}
		if(count || !dim_flag){
			if(array_index == 0){
				int (*function)(const std::vector<double> &,const std::vector<int> &,int,int,std::vector<double> **,double *);
				function = &probabilistic;
				int k_vec = 3;
				for(int l = 0;l<num_HT;l++){
					LSH[l] = new LSH_Curve(num_grid,dim,k_vec,250,(*n)/4,l,function);
				}
			}
			char * id = (char *)malloc(sizeof(char) *(splitted[0].size() +1));
			strcpy(id,splitted[0].c_str());
			new_curve = new Curve_Info(curve_points,id);
			(*curve_info)[array_index] = new_curve;
			for(int l = 0;l<num_HT;l++){
					LSH[l]->LSH_Insert(array_index);
			}
			array_index++;
		}
		count++;
	}

	for(int i = array_index;array_index<*n;i++){
		(*curve_info)[i] = NULL;
	}

	myfile.close();
	return LSH;
}