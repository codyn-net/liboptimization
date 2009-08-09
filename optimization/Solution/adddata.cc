#include "solution.ih"

void Solution::addData(string const &name, ExtensionData *data) 
{
	map<string, ExtensionData *>::iterator iter = d_data->extensionData.find(name);
	
	if (iter != d_data->extensionData.end())
	{
		delete iter->second;
		d_data->extensionData.erase(iter);
	}

	d_data->extensionData[name] = data;
}
