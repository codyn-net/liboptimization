#include "extension.ih"

void Optimizer::Extension::save()
{
	vector<Cloneable<Solution> > sols = d_data->optimizer->solutions();
	vector<Cloneable<Solution> >::iterator iter;
	
	for (iter = sols.begin(); iter != sols.end(); ++iter)
	{
		save(**iter);
	}	
}
