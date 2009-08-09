#include "fitness.ih"

void Fitness::update(map<string, double> const &fitness) 
{
	d_data->components = fitness;

	if (!d_data->state)
	{
		compile();
	}
	
	if (!d_data->state)
	{
		return;
	}

	map<string, double>::const_iterator iter;
	
	for (iter = fitness.begin(); iter != fitness.end(); ++iter)
	{
		CpgProperty *property = cpg_object_get_property(d_data->state, iter->first.c_str());
		
		if (property)
		{
			cpg_property_set_value(property, iter->second);
		}
	}
	
	cpg_object_reset_cache (d_data->state);
	
	if (d_data->expression)
	{
		cpg_expression_reset_cache (d_data->expression);
	}
}
