#include "solution.ih"

Solution::operator string() const
{
	return String::join(d_data->parameters.values(), ", ");
}
