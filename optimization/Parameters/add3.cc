#include "parameters.ih"

container::Parameter &Parameters::add(string const &name, Boundaries::value_type const &boundary) 
{
	container::Parameter parameter = {name, boundary, 0};
	return add(parameter);
}
