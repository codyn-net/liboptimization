#include "solution.ih"

void Solution::setFitness(Fitness const &fitness) 
{
	d_data->fitness = fitness.copy();
}
