#include "webots.ih"

Webots &Webots::instance() 
{
	if (!s_instance)
	{
		s_instance = new Webots();
	}
	
	return *s_instance;
}
