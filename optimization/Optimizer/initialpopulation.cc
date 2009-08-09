#include "optimizer.ih"

void Optimizer::initialPopulation()
{
	for (size_t i = 0; i < d_data->populationSize; ++i)
	{
		Solution *solution = createSolution(i);
		solution->reset();
		
		addSolution(*solution);
		delete solution;
	}
}
