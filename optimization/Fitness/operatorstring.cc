#include "fitness.ih"

Fitness::operator string() const
{
	return String::join(values(), ", ");
}
