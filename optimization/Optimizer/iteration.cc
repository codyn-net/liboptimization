#include "optimizer.ih"

bool Optimizer::iteration()
{
	vector<Cloneable<Solution> > sols = solutions();
	vector<Cloneable<Solution> >::iterator iter;

	// Determine best solution from current iteration
	for (iter = sols.begin(); iter != sols.end(); ++iter)
	{
		Solution &solution = **iter;

		if (!d_data->best || solution.fitness() > d_data->best->fitness())
		{
			d_data->best = solution.copy();
		}
	}
	
	save();

	// Increase iteration, returns false when there is a stopping condition
	if (done())
	{
		return false;
	}

	vector<Cloneable<Extension> >::iterator it;
	
	for (it = d_data->extensions.begin(); it != d_data->extensions.end(); ++it)
	{
		if ((*it)->done())
		{
			return false;
		}
	}
	
	update();
	return true;
}
