#include "optimizer.ih"

void Optimizer::save()
{
	if (!d_data->db)
	{
		initializeDatabase();
	}
	
	if (!d_data->db)
	{
		return;
	}
	
	if (d_data->iteration == 0)
	{
		initializeFitnessTable();
	}
	
	int bestid = -1;
	double bestfitness = 0;
	
	if (d_data->best)
	{
		Solution &best = d_data->best;

		bestid = best.id();
		bestfitness = best.fitness().value();
	}
	
	char const *s = d_data->random.state();
	string state = String::hex(s, d_data->random.stateSize());
	
	// Insert iteration stuff
	d_data->db.query() << "INSERT INTO iteration ("
	                   << "`iteration`, `best_id`, `best_fitness`, "
	                   << "`random_state`, `time`) VALUES ("
	                   << currentIteration() << ", "
	                   << bestid << ", "
	                   << bestfitness << ", X'"
	                   << state << "', "
	                   << time(0) << ")"
	                   << SQLite::Query::end();

	// Iterate over all solutions and save them
	vector<Cloneable<Solution> > sols = solutions();
	vector<Cloneable<Solution> >::iterator iter;
	
	d_data->db.begin();
	
	for (iter = sols.begin(); iter != sols.end(); ++iter)
	{
		save(**iter);
	}
	
	d_data->db.commit();

	vector<Cloneable<Extension> >::iterator it;
	
	for (it = d_data->extensions.begin(); it != d_data->extensions.end(); ++it)
	{
		d_data->db.begin();
		
		(*it)->save();
		
		d_data->db.commit();
	}	
}
