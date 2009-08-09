#include "fitness.ih"

Fitness *Fitness::clone() const
{
	return new Fitness(*this);
}
