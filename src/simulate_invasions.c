# include <stdlib.h>
# include <stdio.h>
# include "params.h"
# include "simulate.h"


void simulate_invasion(){
	if(P.print_details) {
		print_invasions_header_full();
		V.print_function = &print_invasions_full;
	} else {
		print_invasions_header();
		V.print_function = &print_invasions;
	}

	for(V.w = P.Wmin; V.w <= P.Wmax; V.w+=P.Wstep){
		for(V.M = P.Mmin; V.M <= P.Mmax; V.M+=P.Mstep){
			for(V.contrite1 = 1; V.contrite1 < 2; V.contrite1+=1){
				for(V.contrite2 = 1; V.contrite2 < 2; V.contrite2+=1){
					//V.d1 = -1; V.d2 = -1; simulate_interaction(); //ALLD vs ALLD.
					for(V.d1 = P.Dmin; V.d1 <= P.Dmax; V.d1+=P.Dstep){
						V.d2 = -1;  simulate_interaction(); //d1 vs ALLD.
						for(V.d2 = P.Dmin; V.d2 <= P.Dmax; V.d2+=P.Dstep){
							//if(V.d1 == V.d2 && V.contrite1 == 1 && V.contrite2 == 1 )//temporary for quick calibration @ vgg
							//simulate_interaction(); //vs cooperative opponent
						}
					}
				}
			}
		}
	}
}


void print_invasions_header_full(){
	/*reputations go: ABab -- where capitals are player A's opinions, and letters represent who they are an opinion of. 1 is good, 0 is bad. This yields a binary number, and the corresponding integer in the rep_history gets incremented when we're in this state.
	So we have:

	 0 = 0000 = BBbb
	 1 = 0001 = BBbg
	 2 = 0010 = BBgb
	 3 = 0011 = BBgg
	 4 = 0100 = BGbb
	 5 = 0101 = BGbg
	 6 = 0110 = BGgb
	 7 = 0111 = BGgg
	 8 = 1000 = GBbb
	 9 = 1001 = GBbg
	10 = 1010 = GBgb
	11 = 1011 = GBgg
	12 = 1100 = GGbb
	13 = 1101 = GGbg
	14 = 1110 = GGgb
	15 = 1111 = GGgg

	Actually, screw it, let's just use binary column labels.

	*/

	printf("W,\tM,\tT,\ts1,\ts2,\td1,\td2,\tA,\tB,\ta,\tb,\tK,\tk,\t0000,\t0001,\t0010,\t0011,\t0100,\t0101,\t0110,\t0111,\t1000,\t1001,\t1010,\t1011,\t1100,\t1101,\t1110,\t1111\n");
}
void print_invasions_header(){
	//printf("W, M, T, s1, s2, d1, d2, A, B, a, b, K, k \n");
	printf("W, M, T, s1, s2, d1, d2, K, k \n");
}


void print_invasions_full(){
	printf("%f,\t%f,\t%d,\t%d,\t%d,\t%f,\t%f,\t%d,\t%d,\t%d,\t%d,\t%d,\t%d,\t%d,\t%d,\t%d,\t%d,\t%d,\t%d,\t%d,\t%d,\t%d,\t%d,\t%d,\t%d,\t%d,\t%d,\t%d,\t%d\t\n",
			V.w, V.M,P.T,V.contrite1, V.contrite2, V.d1,V.d2, V.history[0],V.history[1],V.history[2],V.history[3],V.history[4],V.history[5],
			V.rep_hitory[0],V.rep_hitory[1],V.rep_hitory[2],V.rep_hitory[3],V.rep_hitory[4],V.rep_hitory[5],V.rep_hitory[6],V.rep_hitory[7],V.rep_hitory[8],
			V.rep_hitory[9],V.rep_hitory[10],V.rep_hitory[11],V.rep_hitory[12],V.rep_hitory[13],V.rep_hitory[14],V.rep_hitory[15]);
}
void print_invasions(){
	//printf("%f, %f, %d, %d, %d, %f, %f, %d, %d, %d, %d, %d, %d \n",  V.w, V.M,P.T,V.contrite1, V.contrite2, V.d1,V.d2, V.history[0],V.history[1],V.history[2],V.history[3],V.history[4],V.history[5]);
	printf("%f, %f, %d, %d, %d, %f, %f, %d, %d \n",  V.w, V.M,P.T,V.contrite1, V.contrite2, V.d1,V.d2,V.history[4],V.history[5]);
}





