#include "solution.ih"

int Solution::removeParameter(string const &name)
{
	return d_data->parameters->remove(name);
}
