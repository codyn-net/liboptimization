#include "optimizer.ih"

Optimizer::Optimizer(Parameters const &parameters, Boundaries const &boundaries, Fitness const &fitness)
{
	setup(parameters, boundaries, fitness);
}
