#include "extension.ih"

void Optimizer::Extension::clear()
{
	delete d_data->optimizer;
	d_data->optimizer = 0;
}
