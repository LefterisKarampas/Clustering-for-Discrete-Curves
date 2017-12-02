#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "../include/main_functions.h"
#include "../include/Curve_Info.h"
#include "../include/LSH_Curve.h"
#include "../include/Cluster.h"
#include "../include/Initialization.h"
#include "../include/Assignment.h"
#include "../include/Distance.h"
#include "../include/Update.h"


using namespace std;

Curve_Info** curve_info = NULL;								//Structure for storing the curve's info
double ** Distance_Table = NULL;

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
	LSH_Curve ** LSH;											//LSH Structure
	int n;
	//Read curves and construct Curve's info structure and LSH
	if((LSH = read_curves(input_file,num_HT,num_grid,&curve_info,&n)) == NULL){
		cerr << "Failed read input file" << endl;
		exit(3);
	}
	Distance_Table = (double **)malloc(sizeof(double *)*n);
	for(int i=0;i<n;i++){
		Distance_Table[i] = (double *)malloc(sizeof(double)*(i+1));
		for(int j=0;j<i+1;j++){
			if(i == j){
				Distance_Table[i][j] = 0;
			}
			else{
				Distance_Table[i][j] = -1;
			}
			//cout << Distance_Table[i][j] << "  ";
		}
		//cout << endl;
	}
	long double (*distance)(const T_Curve &,const T_Curve &);
	distance = &(DFT);
	srand(time(NULL));
	Clusters * clusters;
	double objective_value;
	double prev_value;
	int init;
	for(init=0;init<2;init++){
		clusters = new Clusters();
		switch(init){
			case 0:{
				cerr << "K_Means++ Starting now" << endl;
				K_Means_Plusplus(clusters,num_clusters,n,distance);
				break;
			}
			case 1:{
				cerr <<endl << "Random_Initialization Starting now" << endl;
				Random_Initialization(clusters,num_clusters,n);
			}
		}
		int assign;
		for(assign = 0;assign <2;assign++){
			switch(assign){
				case 0:{
					/*objective_value = Lloyd_Assignment(clusters,n,distance);
					for(int i =0;i<num_clusters;i++){
						std::vector<int>  temp = (*clusters)[i].Cluster_Get_Neighbors();
						cout << (*clusters)[i].Cluster_Get_Center() << " " <<temp.size()<< endl;
					}
					do{					
						PAM_Improved(clusters,distance);
						prev_value = objective_value;
						objective_value = Lloyd_Assignment(clusters,n,distance);
						cout << prev_value << " - " << objective_value << endl;
					}while(prev_value != objective_value);
					for(int i =0;i<num_clusters;i++){
						std::vector<int>  temp = (*clusters)[i].Cluster_Get_Neighbors();
						//std::vector<int>  temp_best = (*clusters)[i].Cluster_Get_SecondBest();
						cout << (*clusters)[i].Cluster_Get_Center() << " " <<temp.size()<< endl;
						/*for(int j=0;j<temp.size();j++){
							cout << "\t" << curve_info[temp[j]]->GetId() << " " << temp_best[j] << endl;
						}*/
					break;
					//}
					//break;
				}
				case 1:{
					double prev;
					objective_value = Lloyd_Assignment(clusters,n,distance);
					do{
						prev = objective_value;
						Mean_Discrete_Frechet(clusters,distance);
						objective_value = Lloyd_Assignment(clusters,n,distance);
						cout << prev << " " << objective_value << endl;
					}while(prev != objective_value);
				}
			}
		}
		cout << "---------" <<endl << endl;
		for(int i=0;i<n;i++){
			curve_info[i]->clear_flag();
		}
		delete clusters;
	}

	

	//Destroy the curves and LSH structure
	for(int i=0;i<n;i++){
		if(curve_info[i] != NULL){
			delete curve_info[i];
		}
	}
	delete[] curve_info;

	for(int i =0;i<num_HT;i++){
		delete LSH[i];
	}
	delete[] LSH;

	//Free the allocate space for arguments
	free(input_file);
	free(config_file);
	free(output_file);
	free(metric);
	return 0;
}