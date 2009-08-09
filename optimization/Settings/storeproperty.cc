#include "settings.ih"

base::PropertyBase &Settings::storeProperty(string const &name) 
{
	d_data->storage.push_back("");
		
	return registerProperty<string>(name, d_data->storage.back());	
}
