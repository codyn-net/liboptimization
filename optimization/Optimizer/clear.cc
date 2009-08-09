#include "optimizer.ih"

void Optimizer::clear()
{
	{
		vector<Cloneable<Extension> >::iterator iter;

		for (iter = d_data->extensions.begin(); iter != d_data->extensions.end(); ++iter)
		{
			(*iter)->clear();
		}
	
		d_data->extensions.clear();
	}
	
	{
		vector<Cloneable<Solution> >::iterator iter;

		for (iter = d_data->solutions.begin(); iter != d_data->solutions.end(); ++iter)
		{
			(*iter)->clear();
		}
	
		d_data->solutions.clear();
	}
	
	if (d_data->best)
	{
		d_data->best->clear();
	}
}
