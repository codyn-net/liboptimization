#include "optimizer.ih"

void Optimizer::addExtension(Extension &extension) 
{
	extension.setOptimizer(*this);
	d_data->extensions.push_back(extension);
	
	vector<Cloneable<Solution> >::iterator iter;
	
	for (iter = d_data->solutions.begin(); iter != d_data->solutions.end(); ++iter)
	{
		extension.newSolution(**iter);
	}
}
