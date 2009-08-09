#include "extension.ih"

string const &Optimizer::Extension::name() const
{
	return d_data->name;
}
