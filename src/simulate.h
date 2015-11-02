
#ifndef SIMULATE_H_
#define SIMULATE_H_

# include <stdint.h>


	uint32_t kn[128]; float fn[128];float wn[128]; uint32_t seed;

	//evolution
	void simulate_population();
	void print_evolution_header();
	void print_evolution();
	void map_selection_gradients();

	//evolution: symetric population sampling functions
	double sample_uniform();
	double sample_truncated_normal();


	//invasion
	void simulate_invasion();
	void print_invasions_header_full();
	void print_invasions_header();
	void print_invasions_full();
	void print_invasions();


	//interaction
	void simulate_interaction();
	void simulate_confused_interaction();
	void act_and_record();

	//randomness
	double runiform(double, double);
	int rand_geo(double);

	//strategies
	int get_action_contrite(int, int);
	int get_action_remorseless(int, int);
//	void update_reps_unapologetic_unconfused(int * );
//	void update_reps_unapologetic_confused(int * );
//	void update_reps_concordant(int * );
	void update_reps(double * );

	//common
	void print_nothing();
	int convert_bin2int(int *);





#endif /* SIMULATE_H_ */
