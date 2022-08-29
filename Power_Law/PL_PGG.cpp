#include "PL_PGG.h"
using namespace std;

PL_PGG::PL_PGG(const int siz,const double R,const int deg, const double B, const int FN){
	g0 = 11;
	r_eff = R;
	r_n = R;
	b = B;
	file_n = FN;
	max_group = 0;
	
	if (b + 0.00000001 > 1 && b - 0.00000001 < 1)
		r_n /= 0.69975;

	if (b + 0.00000001 > 2 && b - 0.00000001 < 2 )
		r_n /= 0.95569;
	if (b + 0.00000001 > 0.5 && b - 0.00000001 < 0.5)
		r_n /= 0.797254415;

	d = deg;

	LL = siz;

	Strategy = new int[LL];

	for(int i = 0; i < LL; i++){
		Strategy[i] = rand() % 2;
	}

	for(int i = 0; i < LL; i++){
		vector<int> v;
		Neighbour.push_back(v);
	}

	/* Read from the pre-built graphs
	*/
	char graph_name[100];
	sprintf(graph_name,"GR/graph_%03d.dat", FN);

	FILE *fp = fopen(graph_name,"rt");
	char line[2000];

	while(fgets(line, sizeof(line),fp) != NULL){
		//trim the line
		char *end;
		end = line + strlen(line) - 1;
		while(end > line && isspace((unsigned char)*end)) end--;
  		// Write new null terminator character
  		end[1] = '\0';

  		char * pch = strtok(line,"|");
  		int current_node = atoi(pch);
  		pch = strtok(NULL, " ");
  		while(pch != NULL){
  			Neighbour[current_node].push_back(atoi(pch));
  			pch = strtok(NULL, " ");
  		}
	}
	fclose(fp);

	for(int i = 0; i < LL; i++){
		if( (int) Neighbour[i].size() + 1 > max_group)
			max_group = (int) (Neighbour[i].size() + 1);
	}


	WRS_size = new int[max_group+5];
	for(int j = 0; j < max_group+5;j++)
		WRS_size[j] = 0;

	for(int j = 0; j < LL; j++)
		WRS_size[Neighbour[j].size() + 1] += (Neighbour[j].size() + 1);

}


PL_PGG::~PL_PGG(){
	delete Strategy;
	delete WRS_size;
}

void PL_PGG::see_size(){
	/*
	for(int i = 0; i < Neighbour[0].size(); i++)
		printf("%d\n", Neighbour[0][i]);
	int WRS_coop[max_group + 5];
	for(int j = 0; j < max_group+5;j++)
		WRS_coop[j] = 0;
			
	for(int j = 0; j < LL; j++){
		WRS_coop[Neighbour[j].size() + 1] += Strategy[j];
		for(int k = 0; k < (int) Neighbour[j].size(); k++)
			WRS_coop[Neighbour[j].size() + 1] += Strategy[Neighbour[j][k]];
		}
	*/

	for(int i = 0; i <= max_group; i++)
		printf("%d %d\n", i, WRS_size[i]);


}

double PL_PGG::unit_game(const int cent){
	double gs = (double) (Neighbour[cent].size());
	double r = r_n * pow(( (gs-1) / (g0 -1) ), b);

	if (b + 0.00000001 > 0 && b - 0.00000001 < 0)
		r = r_n;

	double contrib = (double) Strategy[cent];

	for(int i = 0; i < gs; i++){
		int person = Neighbour[cent][i];
		if(Strategy[person] == 1)
			contrib += 1;
	}

	return (contrib * r) / (gs+1);
}


double PL_PGG::centre_game(const int cent){
	double profit = unit_game(cent);
	for(int i = 0; i < Neighbour[cent].size(); i++){
		profit += unit_game(Neighbour[cent][i]);
	}

	profit -= double (Neighbour[cent].size()) * double(Strategy[cent]);

	return profit;
}

int PL_PGG::game(bool ptf){

	FILE *file;
	if(ptf){
		char path[100];
		sprintf(path,"b_%02d_r1_%03d_%03d.dat", (int)((b + 0.000001) * 10), (int)((r_eff + 0.000001) * 10),
			file_n);
		printf("Now file:%s\n",path);
		file = fopen(path,"a+");
	}

	double rate = 0.0;
	int iter = 10001;
	int gap = 500;
	for(int i = 0; i < iter; i++){

		if(i % gap == 0){
			double total = 0;
			for(int j = 0; j < LL; j++)
				total += double(Strategy[j]);

			rate = double (total/double(LL));

			/*

			int WRS_coop[max_group + 5];
			for(int j = 0; j < max_group+5;j++)
				WRS_coop[j] = 0;
			
			for(int j = 0; j < LL; j++){
				WRS_coop[Neighbour[j].size() + 1] += Strategy[j];
				for(int k = 0; k < (int) Neighbour[j].size(); k++)
					WRS_coop[Neighbour[j].size() + 1] += Strategy[Neighbour[j][k]];
			}

			char all_outcome[500] = "";
			for(int j = 1; j < max_group+1; j++){ //No need to do zero
				char one_outcome[20] = "";
				if(WRS_size[j] == 0)
					continue;
				
				if(ptf)
				sprintf(one_outcome, "%2d:%.3f ",j, double(WRS_coop[j])/double(WRS_size[j]));

				strcat(all_outcome, one_outcome);
			}
			*/


			if(ptf)
				fprintf(file, "%d %d\n", i, rate);
				//fprintf(file, "%d|%.3f|%s\n",i,rate,all_outcome);
			printf("%d %d\n", i, rate);

			//printf("%d|%.3f|%s\n",i, rate, all_outcome);


		}
		if(rate - 0.000001 <= 0 || rate + 0.000001 >= 1 || i == iter -1)
			continue;
		

		for(int j = 0; j < LL; j++){
			int x = rand() % LL;
			if(Neighbour[x].size() == 0)
				continue;
			int y = Neighbour[x][rand() % Neighbour[x].size() ];
			if (Strategy[x] == Strategy[y])
				continue;
			double x_earn = centre_game(x);
			double y_earn = centre_game(y);

			if ((double)rand()/(double)RAND_MAX < 1.0/( 1.0 + exp((y_earn - x_earn)/K) ) )
				Strategy[y] = Strategy[x];
		}
	}
	if(ptf)
		fclose(file);

	return 0;
}

