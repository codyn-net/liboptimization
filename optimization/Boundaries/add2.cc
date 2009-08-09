#include "boundaries.ih"

container::Boundary &Boundaries::add(container::Boundary const &item) 
{
	return Container<container::Boundary>::add(item);
}
