#include "settings.ih"

bool Settings::hasProperty(string const &name) 
{
	if (Properties::hasProperty(name))
		return true;
	
	storeProperty(name);
	return true;
}
