#include "extension.ih"

Optimizer::Extension *Optimizer::Extension::clone() const
{
	return new Optimizer::Extension(*this);
}
