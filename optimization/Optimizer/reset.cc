#include "optimizer.ih"

void Optimizer::reset()
{
	d_data->iteration = 0;
	vector<Cloneable<Solution> >::iterator iter;
	
	for (iter = d_data->solutions.begin(); iter != d_data->solutions.end(); ++iter)
	{
		(*iter)->clear();
	}

	d_data->solutions.clear();
	
	initialPopulation();
	
	d_data->best.clear();
}
