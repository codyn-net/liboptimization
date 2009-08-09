#include "extension.ih"

Optimizer::Extension::Data::~Data() 
{
	if (optimizer)
	{
		delete optimizer;
	}
}
