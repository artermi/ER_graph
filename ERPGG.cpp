#include "ERPGG.h"
using namespace std;

ERPGG::ERPGG(const int siz,const double R,const int deg, const double B){
	g0 = 11;
	r_eff = R;
	r_n = R;
	b = B;
	
	if (b + 0.00000001 > 1 && b - 0.00000001 < 1)
		r_n /= 0.5011889938866062;

	if (b + 0.00000001 > 2 && b - 0.00000001 < 2 )
		r_n /= 0.31025536300404416;
	if (b + 0.00000001 > 0.5 && b - 0.00000001 < 0.5)
		r_n /= 0.682120469333653;

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

	/* Maximum of Edge = (LL-1) * LL / 2
	   If average degree is d, total number of edges would be:
	   d * LL / 2
	   so the probability of forming each edge is d / (LL -1 );
	*/

	for (int i = 0; i < LL; ++i)
	{
		for (int j = 0; j < i; ++j)
		{
			if((double)rand()/(double)RAND_MAX * (LL - 1) < double(deg) ){
				Neighbour[i].push_back(j);
				Neighbour[j].push_back(i);
			}
		}
	}
}
ERPGG::~ERPGG(){
	delete Strategy;
}

double ERPGG::unit_game(const int cent){
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


double ERPGG::centre_game(const int cent){
	double profit = unit_game(cent);
	for(int i = 0; i < Neighbour[cent].size(); i++){
		profit += unit_game(Neighbour[cent][i]);
	}

	profit -= double (Neighbour[cent].size()) * double(Strategy[cent]);

	return profit;
}

int ERPGG::game(bool ptf){

	FILE *file;
	if(ptf){
		char path[100];
		sprintf(path,"b_%02d_r1_%03d.dat", (int)((b + 0.000001) * 10), (int)((r_eff + 0.000001) * 10));
		printf("Now file:%s\n",path);
		file = fopen(path,"a+");
	}

	double rate = 0.0;
	double iter = 10001;
	for(int i = 0; i < iter; i++){

		if(i % 500 == 0){
			double total = 0;
			for(int j = 0; j < LL; j++)
				total += double(Strategy[j]);

			rate = double (total/double(LL));
			if(ptf && i == iter -1)
				fprintf(file, "%06d %.3f\n",i,rate);
			printf("%d %.3f\n",i, rate );

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

