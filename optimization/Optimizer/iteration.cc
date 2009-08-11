#include "optimizer.ih"

bool Optimizer::iteration()
{
	vector<Cloneable<Solution> > sols = solutions();
	vector<Cloneable<Solution> >::iterator iter;

	Cloneable<Solution> curbest = d_data->best ? d_data->best->copy() : 0;

	// Determine best solution from current iteration
	for (iter = sols.begin(); iter != sols.end(); ++iter)
	{
		Solution &solution = **iter;

		if (!d_data->best || solution.fitness() > d_data->best->fitness())
		{
			d_data->best = solution.copy();
		}
	}
	
	log(LogType::Info) << "Iteration " << d_data->iteration << " done (" << (d_data->best ? string(d_data->best->fitness()) : "*") << ")" << Logger::End();
	
	if (!curbest || d_data->best->fitness() > curbest->fitness())
	{
		log(LogType::Info) << "New best solution: " << d_data->best->id() << " = " << d_data->best->fitness().value() << Logger::End();
	}
	
	save();

	// Increase iteration, returns false when there is a stopping condition
	if (done())
	{
		log(LogType::Info) << "Finished" << Logger::End();
		return false;
	}

	vector<Cloneable<Extension> >::iterator it;
	
	for (it = d_data->extensions.begin(); it != d_data->extensions.end(); ++it)
	{
		if ((*it)->done())
		{
			return false;
		}
	}
	
	update();
	return true;
}
