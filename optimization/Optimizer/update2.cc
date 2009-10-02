#include "optimizer.ih"

void Optimizer::update()
{
	// Iterate over all solutions and update them
	vector<Cloneable<Solution> > sols = solutions();
	vector<Cloneable<Solution> >::iterator iter;
	
	for (iter = sols.begin(); iter != sols.end(); ++iter)
	{
		update(**iter);
	}
}
