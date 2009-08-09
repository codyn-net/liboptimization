#include "fitness.ih"

void Fitness::compile()
{
	if (d_data->expression)
	{
		cpg_ref_counted_unref(d_data->expression);
		d_data->expression = 0;
	}
	
	if (d_data->state)
	{
		g_object_unref(d_data->state);
		d_data->state = 0;
	}
	
	if (d_data->settings.propertyExists("expression"))
	{
		string expr = string(settings().property<string>("expression"));
		d_data->expression = cpg_expression_new(expr.c_str());
		
		vector<string> properties = settings().properties();

		d_data->state = cpg_object_new ("container");
		
		for (vector<string>::iterator iter = properties.begin(); iter != properties.end(); ++iter)
		{
			if (String(*iter).startsWith("var:"))
			{
				string nm = iter->substr(4);
				string value = string(settings().property<string>(*iter));
				
				cpg_object_add_property(d_data->state, nm.c_str(), value.c_str(), false);
			}
		}
		
		compileCpg();
	}
}
