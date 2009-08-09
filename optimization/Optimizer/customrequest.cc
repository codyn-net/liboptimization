#include "optimizer.ih"

void Optimizer::customRequest(Solution &solution, messages::worker::Request &request) 
{
	vector<Cloneable<Extension> >::iterator iter;
	
	for (iter = d_data->extensions.begin(); iter != d_data->extensions.end(); ++iter)
	{
		(*iter)->customRequest(solution, request);
	}
}
