#include "optimizer.ih"

bool Optimizer::iteration()
{
	vector<Cloneable<Solution> > sols = solutions();
	vector<Cloneable<Solution> >::iterator iter;

	Cloneable<Solution> curbest = d_data->best ? d_data->best->copy() : 0;
	Fitness &fitness = d_data->fitness;
	
	double bestFitness = d_data->best ? fitness.evaluate(d_data->best->fitness()) : 0;

	// Determine best solution from current iteration
	for (iter = sols.begin(); iter != sols.end(); ++iter)
	{
		Solution &solution = **iter;
		double fit = fitness.evaluate(solution.fitness());

		if (!d_data->best || fit > bestFitness)
		{
			d_data->best = solution.copy();
			bestFitness = fit;
		}
	}
	
	log(LogType::Info) << "Iteration " << d_data->iteration << " done" << Logger::End();
	
	if (!curbest || bestFitness > fitness.evaluate(curbest->fitness()))
	{
		log(LogType::Info) << "New best solution: " << d_data->best->id() << " = " << bestFitness << Logger::End();
	}
	
	save();

	// Increase iteration, returns false when there is a stopping condition
	if (done())
	{
		log(LogType::Info) << "Finished" << Logger::End();
		return false;
	}

	update();
	return true;
}
