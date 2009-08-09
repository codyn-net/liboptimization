#include "fitness.ih"

void Fitness::compileCpg()
{
	GSList *context = g_slist_prepend(NULL, d_data->state);

	if (d_data->state)
	{
		GSList *props;
	
		for (props = cpg_object_get_properties(d_data->state); props; props = g_slist_next(props))
		{
			CpgProperty *property = (CpgProperty *)props->data;
		
			if (!cpg_expression_compile(cpg_property_get_value_expression(property), context, NULL))
			{
				cerr << "Could not compile property: " << cpg_property_get_name(property) << endl;
			}
		}
	}
	
	if (d_data->expression)
	{	
		if (!cpg_expression_compile(d_data->expression, context, NULL))
		{
			cerr << "Could not compile expression: " << cpg_expression_get_as_string(d_data->expression) << endl;
		}
	}
	
	g_slist_free(context);
}
