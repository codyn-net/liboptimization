#include "parameters.ih"

container::Parameter &Parameters::add(string const &name) 
{
	Boundaries::value_type boundary = {name, 0, 0};
	return add(name, boundary);
}
