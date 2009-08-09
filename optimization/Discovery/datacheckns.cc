#include "discovery.ih"

bool Discovery::Data::checkNs(string const &ns) const
{
	return (this->ns == ns);
}
