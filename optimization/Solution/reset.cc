#include "solution.ih"

void Solution::reset()
{
	fitness().reset();
	
	Parameters::iterator iter;	
	size_t pos = 0;

	for (iter = d_data->parameters->begin(); iter != d_data->parameters->end(); ++iter)
	{
		Parameters::value_type &parameter = **iter;
		parameter.value = d_data->random.range(parameter.boundary.min, parameter.boundary.max);
	}
}
