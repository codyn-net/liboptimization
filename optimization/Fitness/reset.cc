#include "fitness.ih"

void Fitness::reset()
{
	compile();

	if (!d_data->state)
	{
		return;
	}

	map<string, double>::iterator iter;
	
	for (iter = d_data->components.begin(); iter != d_data->components.end(); ++iter)
	{
		CpgProperty *property = cpg_object_get_property(d_data->state, iter->first.c_str());
		
		if (property)
		{
			cpg_property_set_value(property, 0);
		}
	}
}
