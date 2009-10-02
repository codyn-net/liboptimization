#include "optimizer.ih"

Optimizer::Optimizer() 
{
	setup(Parameters(), Boundaries(), Fitness());
}
