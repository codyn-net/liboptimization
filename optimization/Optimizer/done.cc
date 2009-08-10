#include "optimizer.ih"

bool Optimizer::done()
{
	return (++d_data->iteration >= d_data->maxIterations);
}
