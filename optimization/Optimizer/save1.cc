#include "optimizer.ih"

void Optimizer::save(Solution &solution)
{
	Fitness &fitness = d_data->fitness;
	double fit = fitness.evaluate(solution.fitness());
	
	d_data->db.query() << "INSERT INTO solution ("
	                   << "`index`, `iteration`, `values`, `value_names`, "
	                   << "`fitness`) VALUES ("
		               << solution.id() << ", "
		               << currentIteration() << ", '"
		               << SQLite::serialize(solution.parameters().values()) << "', '"
		               << SQLite::serialize(solution.parameters().names()) << "', "
		               << fit << ")"
		               << SQLite::Query::end();

	SQLite::Query q = d_data->db.query();
	q << "INSERT INTO `fitness` ("
	  << "`index`, `iteration`, `value`";
	  
	Fitness::Values const &components = solution.fitness();
	Fitness::Values::const_iterator iter;
	stringstream values;
	
	values << "VALUES(" << solution.id() << ", " << currentIteration() << ", " << fit;
	
	for (iter = components.begin(); iter != components.end(); ++iter)
	{
		string norm = normalizeFitnessName(iter->first);
		
		q << ", `_" << norm << "`";
		values << ", " << iter->second;
	}
	
	q << ") " << values.str() << ")" << SQLite::Query::End();
}
