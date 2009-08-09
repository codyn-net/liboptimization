#include "fitness.ih"

Fitness::Fitness()
:
	Object()
{
	d_data = new Data();
	addPrivateData(d_data);
}
