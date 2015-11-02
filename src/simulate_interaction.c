# include <limits.h>
# include <stdio.h>

# include "simulate.h"
# include "params.h"
# include "ziggurat.h"

void simulate_interaction(){

	int i;  int t; int j; double W;

	double ds[4] = {V.d1,-1*V.d1,V.d2,-1*V.d2};

	//set action function according to strategy
	if(V.contrite1 == 0 || V.d1 < 0) V.action1 = &get_action_remorseless; else V.action1 = &get_action_contrite;
	if(V.contrite2 == 0 || V.d2 < 0) V.action2 = &get_action_remorseless; else V.action2 = &get_action_contrite;

	for(i = 0; i <  6; i++){ V.history[i]  = 0;}//start history
	for(i = 0; i < 16; i++){ V.rep_hitory[i]  = 0;}//start reputation state history

	for(t = 0; t < P.T; t++){

		for(i = 0; i < 4; i++){ V.good[i]  = 1;}//everyone starts off good

		if( V.d1 < 0){ V.good[0] = 0;V.good[1] = 0; } //defectors hate everyone
		if( V.d2 < 0){ V.good[2] = 0;V.good[3] = 0; } //defectors hate everyone

		//make sure new_good mirrors good, for efficient updates later
		for(i = 0; i<4; i++){V.new_good[i] = V.good[i];}

		//first turn, always happens
		act_and_record();

		//simulate W **SUBSEQUENT** interactions
		W = rand_geo(V.w)-1; //Geometric number of *subsequent* turns
		for(j = 0; j < W; j++){

			//update signals
			V.signals[1] = r4_nor ( &seed, kn, fn, wn ) + V.actions[1] * V.M; //A's signal of B
			V.signals[2] = r4_nor ( &seed, kn, fn, wn ) + V.actions[0] * V.M; //B's signal of A

			if(P.confused == 1){ //in a confused world, I know what I did, but not what you did...
				if(V.actions[0] > 0) V.signals[0] = INT_MAX; else V.signals[0] = INT_MIN;
				if(V.actions[1] > 0) V.signals[3] = INT_MAX; else V.signals[3] = INT_MIN;
			} else { //in a concordant world, we get the same signal
				V.signals[0] = V.signals[2]; //A's signal of A is B's signal of A
				V.signals[3] = V.signals[1]; //B's signal of B is A's signal of B
			}

			//update reputation, based on signals
			P.Reputation_function(ds);

			//act and record
			act_and_record();
		}
	}
	V.print_function();
}



void act_and_record(){

	V.actions[0] = V.action1(V.good[0], V.good[1]);
	V.actions[1] = V.action2(V.good[3], V.good[2]);

	int i;
	for(i = 0; i < 4; i++){	V.history[i] += V.good[i];	}
	for(i = 0; i < 2; i++){	V.history[4+i] += (V.actions[i]+1)/2;	}
	V.rep_hitory[convert_bin2int(V.good)]++;
}



