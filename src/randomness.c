# include <stdlib.h>
# include <math.h>
# include "params.h"
# include "simulate.h"
# include "ziggurat.h"

double runiform(double a, double b){
	return rand() / (RAND_MAX + 1.0) * (b - a) + a;
}


double rnorm(){
	return r4_nor( &seed, kn, fn, wn );
}

int rand_geo(double w){
	return (int)ceil(log((double)rand() / RAND_MAX)/log(w));
}

double sample_uniform(){
	return runiform(V.D2-V.V, V.D2+V.V);
}

double sample_truncated_normal(){
	double x = -1*RAND_MAX;
	double mean = V.D2;
	double limit = mean;
	//if(mean > 0.5) limit = 1-mean; //nope, big error, d is unbounded on the top!
	double lb = -1*limit;
	double ub = limit;
	while(x < lb || x > ub){
		x = rnorm()*V.V;
	}
	return x + mean;
}


