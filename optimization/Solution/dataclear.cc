#include "solution.ih"

void Solution::Data::clear()
{
	map<string, ExtensionData *>::iterator iter;
	
	for (iter = extensionData.begin(); iter != extensionData.end(); ++iter)
	{
		delete iter->second;
	}
	
	extensionData.clear();
}
