#include "optimizer.ih"

void Optimizer::Data::setSeed(unsigned int const &seed) 
{
	random.seed(seed);
	this->seed = seed;
}
