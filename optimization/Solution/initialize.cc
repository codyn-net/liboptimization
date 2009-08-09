#include "solution.ih"

void Solution::initialize(size_t id, Parameters const &parameters, Fitness const &fitness, Random const &random, Settings const &settings)
{
	d_data = new Data();
	addPrivateData(d_data);
	
	d_data->id = id;
	
	setFitness(fitness);

	d_data->parameters = parameters.copy();
	
	d_data->random = random;
	d_data->settings = settings;
}
