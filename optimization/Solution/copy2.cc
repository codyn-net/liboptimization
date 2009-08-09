#include "solution.ih"

void Solution::copy(Solution const &other)
{
	// Make copies of extensions
	map<string, ExtensionData *>::iterator iter;
	
	for (iter = d_data->extensionData.begin(); iter != d_data->extensionData.end(); ++iter)
	{
		iter->second = iter->second->copy();
	}
}
