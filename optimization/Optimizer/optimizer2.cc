#include "optimizer.ih"

Optimizer::Optimizer() 
{
	initialize(Parameters(), Boundaries(), Fitness());
}
