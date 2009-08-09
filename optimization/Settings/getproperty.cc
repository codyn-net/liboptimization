#include "settings.ih"

PropertyBase &Settings::getProperty(string const &name) 
{
	if (!hasProperty(name))
	{
		return storeProperty(name);
	}

	return Properties::getProperty(name);
}
