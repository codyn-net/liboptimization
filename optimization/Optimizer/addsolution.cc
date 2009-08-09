#include "optimizer.ih"

void Optimizer::addSolution(Solution &solution) 
{
	d_data->solutions.push_back(solution);
	
	vector<Cloneable<Extension> >::iterator iter;
	
	for (iter = d_data->extensions.begin(); iter != d_data->extensions.end(); ++iter)
	{
		(*iter)->newSolution(solution);
	}
}
