#include "boundaries.ih"

Boundaries *Boundaries::copy() const
{
	return new Boundaries(begin(), end());
}
