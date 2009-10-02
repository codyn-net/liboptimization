#include "solution.ih"

Solution *Solution::copy() const
{
	// First, create a new solution
	Solution *ret = new Solution(d_data->id, d_data->parameters, d_data->state);

	// Then have the copy, copy itself from us
	ret->copy(*this);
	return ret;
}
