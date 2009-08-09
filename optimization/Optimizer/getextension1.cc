#include "optimizer.ih"

Optimizer::Extension &Optimizer::getExtension(string const &name) 
{
	vector<Cloneable<Extension> >::iterator iter;
	
	for (iter = d_data->extensions.begin(); iter != d_data->extensions.end(); ++iter)
	{
		if ((*iter)->name() == name)
		{
			return **iter;
		}
	}
}
