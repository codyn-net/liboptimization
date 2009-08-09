#include "optimizer.ih"

Solution &Optimizer::best()
{
	return *d_data->best;
}
