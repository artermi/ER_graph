#include <stdio.h>
#include <math.h>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <string>
#include <cstring>
#include <sys/stat.h>
#include <sys/types.h>


#define K 0.5
class PL_PGG{
public:
	double g0;
	double b;
	double r_n;
	double r_eff;
	int max_group;
	int file_n;
	int LL;
	int d;
	int *WRS_size;
	char dir_name[100];

	int *Strategy;
	std::vector<std::vector<int> > Neighbour;

	PL_PGG(const int siz, const double R, const int deg,const double B, const int FN);
	~PL_PGG();
	void see_size();
	double unit_game(const int cent);
	double centre_game(const int cent);
	int game(bool ptf);
};
