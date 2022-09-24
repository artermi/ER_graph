#include "PL_PGG.h"
using namespace std;


int main(int argc, char** argv){
	srand(time(NULL));
	double para = 6;
	double siz = 5000;
	
	double reff_ = 11;
	double bi_ = 0.5;
	if(argc > 2){
		reff_ =     atof(argv[1]);
		bi_ =     atof(argv[2]);
	}
	
	//printf("Now doing Derermistic mode with size:%d alpha:%f\n",size,para);

	double b_list[4] = {0,0.5,1,2.0};

	for (int bi = 0; bi < 1; ++bi)
		for(double reff = 2; reff < 12.01; reff += 0.1 ){
			bool first_time = true;
			for(int i = 0; i< 10; i++){
				char file_n[100];

				if(first_time){
					sprintf(file_n,"b_%02d_r1_%03d.dat", (int)((b_list[bi] + 0.000001) * 10), (int)((reff + 0.000001) * 10));
					FILE *file;
			  		file = fopen(file_n, "r");
	   				if (file) {
	      				fclose(file);
	      				printf("file:'%s' exists\n",file_n);
	      				break;
	   				}
   				}
   				first_time = false;
   				

				printf("round: %d\n", i);
				PL_PGG gameOBJ(siz, reff,para, b_list[bi],i);
				gameOBJ.game(true);
			}
		}


	return 0;
}
