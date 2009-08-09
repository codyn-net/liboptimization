#include "optimizer.ih"

Solution *Optimizer::createSolution(size_t id) 
{
	return new Solution(id, parameters(), fitness(), random(), settings());
}
