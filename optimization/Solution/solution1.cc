#include "solution.ih"

Solution::Solution(size_t id, Parameters const &parameters, Fitness const &fitness, Random const &random, Settings const &settings)
{
	initialize(id, parameters, fitness, random, settings);
}
