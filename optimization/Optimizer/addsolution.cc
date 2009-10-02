#include "optimizer.ih"

void Optimizer::addSolution(Solution &solution) 
{
	d_data->solutions.push_back(solution);
}
