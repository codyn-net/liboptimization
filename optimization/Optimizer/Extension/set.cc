#include "extension.ih"

void Optimizer::Extension::set(Settings const &settings, string const &name) 
{
	d_data->settings = settings;
	d_data->name = name;
}
