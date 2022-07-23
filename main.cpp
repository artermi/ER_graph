#include "ERPGG.h"
using namespace std;


int main(int argc, char** argv){
	srand(time(NULL));
	double para = 6;
	double siz = 5000;
	/*
	double r = 11;
	double b = 0.5;
	if(argc > 2){
		r =     atof(argv[1]);
		b =     atof(argv[2]);
	}
	*/
	//printf("Now doing Derermistic mode with size:%d alpha:%f\n",size,para);

	double b_list[4] = {0,0.5,1,2.0};
	for (int bi = 0; bi < 4; ++bi)
		for(double reff = 2; reff < 7.01; reff += 0.1 ){
			for(int i = 0; i< 10; i++){
				printf("round: %d\n", i);
				ERPGG gameOBJ(siz, reff,para, b_list[bi]);
				gameOBJ.game(true);
			}
		}


	return 0;
}
