#include "solution.ih"

void Solution::copy(Solution const &other)
{
	// Copy the fitness
	d_data->fitness = other.fitness();
}
