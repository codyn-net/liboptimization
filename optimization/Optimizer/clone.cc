#include "optimizer.ih"

Optimizer *Optimizer::clone() const
{
	return new Optimizer(*this);
}
