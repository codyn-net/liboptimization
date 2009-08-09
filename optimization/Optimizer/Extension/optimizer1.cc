#include "extension.ih"

Optimizer &Optimizer::Extension::optimizer() 
{
	return *d_data->optimizer;
}
