# include <stdlib.h>
# include <math.h>
# include "params.h"
# include "simulate.h"


int convert_bin2int(int * bin_arr) {
    int val = 0;
    int i;
    //for (i = 3; i >= 0; i-- ) {
    for (i = 0; i <= 3; i++ ) {
        val = (val << 1) | bin_arr[i];
    }
    return val;
}

int get_action_contrite(int myRep, int hisRep){
	//if you're bad or you think he's good, cooperate
	if(myRep == 0 || hisRep == 1){
		return 1;
	} else {
		return -1;
	}
}

int get_action_remorseless(int myRep, int hisRep){
	//if he's good, cooperate
	if(hisRep == 1){
		return 1;
	} else {
		return -1;
	}
}




//MAKE THESE GREATER OR EQUAL TO!


void update_reps(double *ds){
	if(ds[0] > 0){
		//can become good any time
		if(V.signals[0] > ds[0]){ V.new_good[0] = 1; }
		if(V.signals[1] > ds[0]){ V.new_good[1] = 1; }

		//can only become bad if your partner is good
		if(V.good[1] == 1 &&  V.signals[0] < ds[1]){ V.new_good[0] = 0; }
		if(V.good[0] == 1 &&  V.signals[1] < ds[1]){ V.new_good[1] = 0; }
	}
	if(ds[2] > 0){
		//can become good any time
		if(V.signals[2] > ds[2]){ V.new_good[2] = 1; }
		if(V.signals[3] > ds[2]){ V.new_good[3] = 1; }

		//can only become bad if your partner is good
		if(V.good[3] == 1 &&  V.signals[2] < ds[3]){ V.new_good[2] = 0; }
		if(V.good[2] == 1 &&  V.signals[3] < ds[3]){ V.new_good[3] = 0; }
	}
	int i;
	for(i = 0; i<4; i++){V.good[i] = V.new_good[i];}
}




/*
 *
 * OLD FUNCTIONS, WHERE YOU COULD BECOME BAD BY DEFECTING ON A BAD GUY
 *
 *
void update_reps_unapologetic_unconfused(double * ds){
	if(V.d1 > 0){
		if(V.signals[0] > ds[0]){ V.good[0] = 1; }
		if(V.signals[0] < ds[1]){ V.good[0] = 0; }

		if(V.signals[1] > ds[0]){ V.good[1] = 1; }
		if(V.signals[1] < ds[1]){ V.good[1] = 0; }
	}
	if(V.d2 > 0){
		if(V.signals[0] > ds[2]){ V.good[2] = 1; }
		if(V.signals[0] < ds[3]){ V.good[2] = 0; }

		if(V.signals[1] > ds[2]){ V.good[3] = 1; }
		if(V.signals[1] < ds[3]){ V.good[3] = 0; }
	}
}


void update_reps_unapologetic_confused(double * ds){
	if(V.d1 > 0){
		if(V.signals[0] > ds[0]){ V.good[0] = 1; }
		if(V.signals[0] < ds[1]){ V.good[0] = 0; }

		if(V.signals[1] > ds[0]){ V.good[1] = 1; }
		if(V.signals[1] < ds[1]){ V.good[1] = 0; }
	}
	if(V.d2 > 0){
		if(V.signals[2] > ds[2]){ V.good[2] = 1; }
		if(V.signals[2] < ds[3]){ V.good[2] = 0; }

		if(V.signals[3] > ds[2]){ V.good[3] = 1; }
		if(V.signals[3] < ds[3]){ V.good[3] = 0; }
	}
}



//REPUTATION UPDATE FUNCTIONS
void update_reps_concordant(double * ds){
	if(ds[0] > 0){ //ignore ALLD
		//can befome good any time
		if(V.signals[0] > ds[0]){ V.new_good[0] = 1; }
		if(V.signals[1] > ds[0]){ V.new_good[1] = 1; }

		//can only become bad if your partner is good
		if(V.good[1] == 1 &&  V.signals[0] < ds[1]){ V.new_good[0] = 0; }
		if(V.good[0] == 1 &&  V.signals[1] < ds[1]){ V.new_good[1] = 0; }
	}
	if(ds[2] > 0){ //ignore ALLD
		//can befome good any time
		if(V.signals[0] > ds[2]){ V.new_good[2] = 1; }
		if(V.signals[1] > ds[2]){ V.new_good[3] = 1; }

		//can only become bad if your partner is good
		if(V.good[3] == 1 &&  V.signals[0] < ds[3]){ V.new_good[2] = 0; }
		if(V.good[2] == 1 &&  V.signals[1] < ds[3]){ V.new_good[3] = 0; }
	}
	int i;
	for(i = 0; i<4; i++){V.good[i] = V.new_good[i];}
}



*/
