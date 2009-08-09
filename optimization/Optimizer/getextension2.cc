#include "optimizer.ih"

Optimizer::Extension const &Optimizer::getExtension(string const &name) const
{
	vector<Cloneable<Extension> >::const_iterator iter;
	
	for (iter = d_data->extensions.begin(); iter != d_data->extensions.end(); ++iter)
	{
		if ((*iter)->name() == name)
		{
			return **iter;
		}
	}	
}
