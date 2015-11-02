/*
 * simulate.c
 *
 *  Created on: 31/03/2014
 *      Author: maciek
 *
 *
 * A, B, a, b: reputation, 1 or 0, of agents A and B, according to A (captital) and b (lower case)
 * C, c: whether each cooperated, 1 or 0
 *
 *
 */

	# include <math.h>
	# include <stdio.h>
	# include <stdlib.h>
	# include <time.h>
	# include <stdint.h>

	# include "params.h"
	# include "simulate.h"
	# include "ziggurat.h"
	# include "ini.h"


int main(int argc, char *argv[]){

	//crank up the random number generator
	srand(time(NULL));
	r4_nor_setup ( kn, fn, wn );
	seed = time(NULL);

	//read parameter file
	set_params_from_command_line(argc, argv);

	//simulate
	P.Simulation_function();
	/*
	int i;
	double j;
	V.D2 = .4;
	V.V = .2;
	for(i =0; i< 1000000; i++){
		//j = rand_geo(0.95);
		j = sample_truncated_normal(0.95);
		printf("%f\n", j);
	}
	*/
	return 0;
}




