#include "optimizer.ih"

Optimizer::Optimizer(Parameters const &parameters, Boundaries const &boundaries, Fitness const &fitness)
{
	initialize(parameters, boundaries, fitness);
}
