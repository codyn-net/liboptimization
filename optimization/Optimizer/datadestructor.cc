#include "optimizer.ih"

Optimizer::Data::~Data()
{
	vector<Cloneable<Solution> >::iterator iter;

	for (iter = solutions.begin(); iter != solutions.end(); ++iter)
	{
		(*iter)->clear();
	}
}
