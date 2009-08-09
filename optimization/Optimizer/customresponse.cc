#include "optimizer.ih"

void Optimizer::customResponse(Solution &solution, messages::worker::Response &response) 
{
	vector<Cloneable<Extension> >::iterator iter;
	
	for (iter = d_data->extensions.begin(); iter != d_data->extensions.end(); ++iter)
	{
		(*iter)->customResponse(solution, response);
	}
}
