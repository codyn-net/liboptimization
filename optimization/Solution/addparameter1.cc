#include "solution.ih"

Parameters::value_type &Solution::addParameter(string const &name, Boundaries::value_type const &boundary)
{
	Parameters::value_type value = {name, boundary, 0};
	return addParameter(value);
}
