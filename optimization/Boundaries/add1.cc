#include "boundaries.ih"

container::Boundary &Boundaries::add(string const &name, double min, double max) 
{
	container::Boundary item = {name, min, max};
	return add(item);
}
