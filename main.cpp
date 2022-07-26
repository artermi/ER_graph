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
				char file_n[100];
				sprintf(file_n,"b_%02d_r1_%03d_%03d.dat", (int)((b_list[bi] + 0.000001) * 10), (int)((reff + 0.000001) * 10),
				i);
				FILE *file;
		  		file = fopen(file_n, "r");
   				if (file) {
      				fclose(file);
      				printf("file:'%s' exists\n",file_n);
      				continue;
   				}

				printf("round: %d\n", i);
				ERPGG gameOBJ(siz, reff,para, b_list[bi],i);
				gameOBJ.game(true);
			}
		}


	return 0;
}
