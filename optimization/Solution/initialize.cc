#include "solution.ih"

void Solution::initialize(size_t id, Parameters const &parameters, State const &state)
{
	d_data = new Data();
	addPrivateData(d_data);
	
	d_data->id = id;
	
	// Make a copy of the parameters
	Parameters *copy = parameters.copy();
	d_data->parameters = *copy;
	delete copy;
	
	d_data->state = state;
}
