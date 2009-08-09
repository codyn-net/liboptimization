#include "solution.ih"

Solution *Solution::clone() const
{
	return new Solution(*this);
}
