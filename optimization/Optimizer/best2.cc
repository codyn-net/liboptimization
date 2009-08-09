#include "optimizer.ih"

Solution const &Optimizer::best() const
{
	return *d_data->best;
}
