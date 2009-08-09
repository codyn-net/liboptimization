#include "extension.ih"

Optimizer::Extension::Extension() 
{
	d_data = new Data();
	addPrivateData(d_data);
	
	d_data->optimizer = 0;
}
