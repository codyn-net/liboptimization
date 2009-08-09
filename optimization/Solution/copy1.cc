#include "solution.ih"

Solution *Solution::copy() const
{
	Solution *ret = new Solution(d_data->id, d_data->parameters, fitness(), d_data->random, d_data->settings);

	ret->copy(*this);
	return ret;
}
