#include "boundaries.ih"

Boundaries *Boundaries::clone() const
{
	return new Boundaries(*this);
}
