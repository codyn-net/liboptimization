#include "fitness.ih"

Fitness *Fitness::copy() const
{
	Fitness *cp = new Fitness();
	
	cp->d_data->settings = d_data->settings;
	cp->d_data->components = d_data->components;
	cp->d_data->name = d_data->name;
	
	if (d_data->expression)
	{
		cp->d_data->expression = cpg_expression_new(cpg_expression_get_as_string(d_data->expression));
	}
	
	if (d_data->state)
	{
		cp->d_data->state = _cpg_object_copy(d_data->state);
	}
	
	cp->compileCpg();
	return cp;
}
