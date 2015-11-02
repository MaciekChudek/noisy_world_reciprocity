
#ifndef PARAMS_H_
#define PARAMS_H_

	#define MIN(a,b) (((a)<(b))?(a):(b))
	#define MAX(a,b) (((a)>(b))?(a):(b))

	void set_params_from_command_line(int argc, char *argv[]);
	void usage(char*);

	typedef struct
	{
	  //relatedness
	  double Rstep;
	  double Rmin;
	  double Rmax;

	  //interaction frequencies
	  double Wstep;
	  double Wmin;
	  double Wmax;

	  //d-strategies
	  double Dstep;
	  double Dmin;
	  double Dmax;

	  //s-strategies
	  double Pstep;

	  //signal strength
	  double Mstep;
	  double Mmin;
	  double Mmax;

	  //evolution variability
	  double Vstep;
	  double Vmin;
	  double Vmax;

	  //sim length
	  int T; //Turns to simulate
	  int G; //Generations
	  int N; //Pairs per generation


	  int confused;
	  int print_details;
	  double BoC; // b over c ratio

	  void (*Simulation_function)();
	  void (*Interaction_function)();
	  void (*Reputation_function)();
	  double (*Truncated_Sample_function)();

	} Parameters;



	//Variables
	typedef struct
	{


		//variables for pairwise simulation
		double signals[4];
		int actions[2];
		int good[4];
		int new_good[4];
		int history[6];
		int rep_hitory[16];


		//parameter iteractors
		double M;
		double V;
		double w;
		int g;

		//population varaibles
		double D;
		double D2;
		double P;
		double P2;

		//functions
		int (*action1)(int, int);
		int (*action2)(int, int);
		void (*print_function)();

		int contrite1;
		int contrite2;
		double d1;
		double d2;

		int runID;

		double tbar;
	} Variables;

	extern Parameters P;
	extern Variables V;



	int param_handler(void*, const char*, const char*, const char*);

#endif /* PARAMS_H_ */

