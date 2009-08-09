#include "settings.ih"

bool Settings::propertyExists(string const &name) 
{
	return Properties::hasProperty(name);
}
