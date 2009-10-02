#include "solution.ih"

Parameters::value_type &Solution::addParameter(Parameters::value_type const &other)
{
	return d_data->parameters.add(other);
}
