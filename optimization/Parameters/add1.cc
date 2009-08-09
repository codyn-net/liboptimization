#include "parameters.ih"

container::Parameter &Parameters::add(container::Parameter const &item) 
{
	return Container<container::Parameter>::add(item);
}
