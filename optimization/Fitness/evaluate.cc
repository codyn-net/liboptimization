#include "fitness.ih"

double Fitness::evaluate(Values const &fitness) 
{
	if (!d_data->state)
	{
		compile();
	}
	
	double ret;
	
	if (!d_data->state)
	{
		ret = fitness.begin() != fitness.end() ? fitness.begin()->second : 0;
	}
	else
	{
		Values::const_iterator iter;
	
		for (iter = fitness.begin(); iter != fitness.end(); ++iter)
		{
			CpgProperty *property = cpg_object_get_property(d_data->state, iter->first.c_str());
		
			if (property)
			{
				stringstream s;
				s << iter->second;
			
				cpg_property_set_value_expression(property, s.str().c_str());
			}
		}
	
		cpg_object_reset_cache (d_data->state);
	
		if (d_data->expression)
		{
			cpg_expression_reset_cache(d_data->expression);
		}
	
		compileCpg();
		ret = d_data->expression ? cpg_expression_evaluate(d_data->expression) : 0;
	}
	
	return isnan(ret) ? 0 : ret;
}
