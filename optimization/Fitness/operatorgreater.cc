#include "fitness.ih"

bool Fitness::operator>(Fitness const &other) const
{
	return value() > other.value();
}
