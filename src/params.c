
#include "params.h"
# include "simulate.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "ini.h"


void print_nothing(){
	return;
}

Parameters P = {
	//relatedness
	.Rstep=.05,
	.Rmin=0,
	.Rmax=.25,
	//ws
	.Wstep = .04,
	.Wmin = .95,
	.Wmax = .99,
	//d-strategies
	.Dstep = .2,
	.Dmin = .1,
	.Dmax = 3,
	//p-strategies
	.Pstep = 0.05,

	//signal strength
	.Mstep = 0.5,
	.Mmin = 0.5,
	.Mmax = 2,

	//evolution variability
	.Vstep = 0.15,
	.Vmin = 0.01,
	.Vmax = 0.31,

	//sim length
	.T = 1, //Turns to simulate
	.G = 1, //Generations
	.N = 1, //Pairs per generation

	.confused = 0,
	.print_details = 0,
	.BoC = 2,
	.Simulation_function = &simulate_invasion,
	.Interaction_function = &simulate_interaction,
	.Reputation_function = &update_reps,
	.Truncated_Sample_function = &sample_uniform
};



Variables V = {
		.signals = {0,0},
		.actions = {0,0},
		.good = {1,1,1,1},
		.new_good = {1,1,1,1},
	    .history = {0,0,0,0,0,0}, //A,B,a,b,C,c
	    .rep_hitory = {0,},


		 .contrite1 = 0,
		 .contrite2 = 0,
		 .d1 = 0,
		 .d2 = 0,
		 .M = 0,
		 .g = 0,


		.print_function = print_nothing,
		.action1 = get_action_contrite,
		.action2 = get_action_contrite,

		.runID = 0
};














void usage(char *name){
	fprintf (stderr, "\
	Usage: %s [OPTIONS]\n \
	Simulates the 'Noisy World Reciprocity' model \n\
	\n\
	-p   parameters file \n\
	\n\
	", name);
	exit(0);
}




void set_params_from_command_line(int argc, char *argv[]){

	int i;
	char *filename = "";
	//char *filename = "temp_params.ini";
	for (i=1; i< argc; i++) {
	     if(argv[i][0] == '-'){
			 if (argv[i][1] == 'h') usage(argv[0]);
	    	 if (argv[i][1] == 'p') filename = argv[i+1];
	    }
	}
	if(strcmp(filename, "") != 0){
		fprintf (stderr,"Attempting to load params from file: %s'\n", filename);
		if (ini_parse(filename, &param_handler,NULL) < 0) {
			fprintf (stderr,"Can't load parameter file, using defaults'\n");
			//exit(1);
		}
	}
	return;
}


int strcmp(char *string1, char *string2);

int param_handler(void* user, const char* section, const char* name2, const char* value2)
{
	char * name = (char *)name2; //to get rid of annoying compiler warnings.
	char * value = (char *)value2; //to get rid of annoying compiler warnings.
	#define IS(n) strcmp(name, n) == 0

	fprintf (stderr,"Parsing parameter %s = %s \n", name, value);

     	 if (IS("Rstep"))	{ P.Rstep = atof(value);}
    else if (IS("Rmin")) 	{ P.Rmin = atof(value);}
    else if (IS("Rmax")) 	{ P.Rmax = atof(value);}
    else if (IS("Wstep")) 	{ P.Wstep = atof(value);}
    else if (IS("Wmin")) 	{ P.Wmin = atof(value);}
    else if (IS("Wmax")) 	{ P.Wmax = atof(value);}
    else if (IS("Dstep")) 	{ P.Dstep = atof(value);}
    else if (IS("Dmin")) 	{ P.Dmin = atof(value);}
    else if (IS("Dmax")) 	{ P.Dmax = atof(value);}
    else if (IS("Pstep")) 	{ P.Pstep = atof(value);}
    else if (IS("Mstep")) 	{ P.Mstep = atof(value);}
    else if (IS("Mmin")) 	{ P.Mmin = atof(value);}
    else if (IS("Mmax")) 	{ P.Mmax = atof(value);}
    else if (IS("Vstep")) 	{ P.Vstep = atof(value);}
    else if (IS("Vmin")) 	{ P.Vmin = atof(value);}
    else if (IS("Vmax")) 	{ P.Vmax = atof(value);}
    else if (IS("T_exp")) 	{ P.T = (int) pow((double) 10,atof(value));}
    else if (IS("G_exp")) 	{ P.G = (int) pow((double) 10,atof(value));}
    else if (IS("N_exp")) 	{ P.N = (int) pow((double) 10,atof(value));}
    else if (IS("BoC")) 	{ P.BoC = atof(value);}
    else if (IS("Confusion")) 	{
    	if(strcmp(value, "true") == 0 || strcmp(value, "1") == 0){
    		P.confused = 1;
    		fprintf (stderr,"  Using confused interations\n");
    	}
    }
    else if (IS("PrintDetails")) 	{
        	if(strcmp(value, "true") == 0 || strcmp(value, "1") == 0){
        		P.print_details = 1;
        		fprintf (stderr,"  Printing detailed output\n");
        	}
        }
    else if (IS("MapGradients")) 	{
    	if(strcmp(value, "true") == 0 || strcmp(value, "1") == 0){
    		P.Simulation_function = &map_selection_gradients;
    		fprintf (stderr,"  Mapping selection gradients\n");
    	}
    }
    else if (IS("TruncateNorm")) 	{
    	if(strcmp(value, "true") == 0 || strcmp(value, "1") == 0){
    		P.Truncated_Sample_function = &sample_truncated_normal;
    		fprintf (stderr,"  Sampling from truncated normal distro\n");
    	}
    }
    else{ return 0;  /* unknown section/name, error */}
    return 1;
}


