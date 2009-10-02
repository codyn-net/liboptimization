#include "solution.ih"

void Solution::reset()
{
	d_data->fitness.clear();
	
	Parameters::iterator iter;	
	size_t pos = 0;

	for (iter = d_data->parameters.begin(); iter != d_data->parameters.end(); ++iter)
	{
		Parameters::value_type &parameter = **iter;
		parameter.value = d_data->state.random.range(parameter.boundary.min, parameter.boundary.max);
	}
	
	d_data->data = "";
}
