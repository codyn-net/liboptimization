#include "parameters.ih"

vector<double> Parameters::values() const
{
	vector<double> ret;
	
	for (const_iterator iter = begin(); iter != end(); ++iter)
	{
		ret.push_back((*iter)->value);
	}
	
	return ret;	
}
