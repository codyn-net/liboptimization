#include "optimizer.ih"

void Optimizer::clear()
{
	d_data->solutions.clear();
	
	if (d_data->best)
	{
		d_data->best.clear();
	}
}
