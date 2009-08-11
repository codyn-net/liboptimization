#include "fitness.ih"

double Fitness::value() const
{
	if (!d_data->expression)
	{
		if (!d_data->components.empty())
		{
			return d_data->components.begin()->second;
		}
		
		return 0;
	}
	
	double v = cpg_expression_evaluate(d_data->expression);
	
	if (isnan(v))
	{
		return 0;
	}
}
