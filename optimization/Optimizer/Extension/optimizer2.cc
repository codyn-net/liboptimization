#include "extension.ih"

Optimizer const &Optimizer::Extension::optimizer() const
{
	return *d_data->optimizer;
}
