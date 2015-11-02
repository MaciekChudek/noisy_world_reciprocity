# include <stdlib.h>
# include <stdio.h>

# include "params.h"
# include "simulate.h"


//EVOLUTION SIMULATION

void map_selection_gradients(){
	print_evolution_header();
	V.print_function = &print_nothing;
	V.tbar = P.T / (1-V.w);
	V.runID = 0;
	for(V.w = P.Wmin; V.w <= P.Wmax; V.w+=P.Wstep){
		for(V.M = P.Mmin; V.M <= P.Mmax; V.M+=P.Mstep){
			for(V.V = P.Vmin; V.V <= P.Vmax; V.V+=P.Vstep){
				double dmin;
				dmin = MAX(P.Dmin,V.V);
				for(V.D = dmin; V.D <= P.Dmax; V.D+=P.Dstep){
					double pmin = 0;//V.V;
					double pmax = 1;//1-V.V;
					for(V.P = pmin; V.P <= pmax; V.P+=P.Pstep){
						V.runID++;
						simulate_population();
					}
				}
			}
		}
	}
}

void simulate_population(){
/*
 * Assumes the following global variables are set:
 * V.runID, V.M, V.V, V.D,
 *
 * And all the parameters.
 *
 *
 *
 */
	 //scale down so we don't overflow the max double size

	double tot = 0; double dsum = 0; double ssum = 0; double x1; double x2; int n;



	//print_evolution(runID,0, P, D, w, M, T,N, 0, 0, 0);
	V.g = 0; V.D2 = V.D; V.P2 = V.P;

	for(V.g = 1; V.g <= P.G; V.g++){ //for G generations

		tot = 0; dsum = 0; ssum = 0;

		for(n = 0; n < P.N; n++){ //for N  pairs
			//pick two strategies from this population
			V.contrite1 = ( V.P2 > ( (double) rand() / RAND_MAX)  );
			V.contrite2 = ( V.P2 > ( (double) rand() / RAND_MAX)  );




			//uniform random... for symmetry, if not accuracy
			//V.d1 =  runiform(V.D2-V.V, V.D2+V.V);
			V.d1 =  P.Truncated_Sample_function();
			V.d2 =  P.Truncated_Sample_function();

			//interact them
			simulate_interaction();

			//accumulate fitness
			x1 = V.history[4] / V.tbar; //number of times s1 cooperated
			x2 = V.history[5] / V.tbar; //number of times s2 cooperated
			tot += (P.BoC-1)*(x1+x2); //total fitness generated = (b-c)*(number of cooperative acts)
			dsum += V.d1*(P.BoC*x2 - x1) + V.d2*(P.BoC*x1 - x2); //fitness weighted by d
			ssum += V.contrite1*(P.BoC*x2 - x1) + V.contrite2*(P.BoC*x1 - x2); //fitness weighted by d
		} //END T LOOP

		V.D2 = dsum/tot;
		V.P2 = ssum/tot;
	} //END G LOOP

	print_evolution();
}

void print_evolution_header(){
	//printf("runID, g, p, d, W, M, T, N, dsum, ssum, tot\n");
	printf("runID, g, W, M, T, N, V, p, d, p2, d2\n");
}

void print_evolution(){
	//printf("%d, %d, %f, %f, %f, %f, %d, %d, %f, %f, %f\n",  runID, G, p, d, W, M, T, N,  dsum, ssum, tot);
	printf("%d, %d, %f, %f, %d, %d, %f, %f, %f, %f, %f\n",  V.runID,  V.g,  V.w, V.M, P.T, P.N, V.V,  V.P,  V.D,  V.P2,  V.D2);
}


