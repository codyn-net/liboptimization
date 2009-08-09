#include "optimizer.ih"

void Optimizer::setup(Parameters const &parameters, Boundaries const &boundaries, Fitness const &fitness)
{
	d_data->parameters = parameters;
	d_data->boundaries = boundaries;
	d_data->fitness = fitness;	
}
