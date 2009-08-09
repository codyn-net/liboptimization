#include "optimizer.ih"

void Optimizer::update()
{
	// Iterate over all solutions and update them
	vector<Cloneable<Solution> > sols = solutions();
	vector<Cloneable<Solution> >::iterator iter;
	
	for (iter = sols.begin(); iter != sols.end(); ++iter)
	{
		update(**iter);
	}

	vector<Cloneable<Extension> >::iterator it;
	
	for (it = d_data->extensions.begin(); it != d_data->extensions.end(); ++it)
	{
		(*it)->update();
	}
}
