#include "optimizer.ih"

void Optimizer::Data::setSeed(unsigned int const &seed) 
{
	state.random.seed(seed);
	this->seed = seed;
}
