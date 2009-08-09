#include "fitness.ih"

Fitness::Data::~Data()
{
	if (expression)
	{
		cpg_ref_counted_unref(expression);
	}
	
	if (state)
	{
		g_object_unref(state);
	}
}
