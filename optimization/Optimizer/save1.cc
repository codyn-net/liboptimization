#include "optimizer.ih"

void Optimizer::save(Solution &solution)
{
	vector<double> fitness = solution.fitness().values();

	d_data->db.query() << "INSERT INTO solution ("
	                   << "`index`, `iteration`, `values`, `value_names`, "
	                   << "`fitness`) VALUES ("
		               << solution.id() << ", "
		               << currentIteration() << ", '"
		               << SQLite::serialize(solution.parameters().values()) << "', '"
		               << SQLite::serialize(solution.parameters().names()) << "', "
		               << solution.fitness().value() << ")"
		               << SQLite::Query::end();

	SQLite::Query q = d_data->db.query();
	q << "INSERT INTO `fitness` ("
	  << "`index`, `iteration`, `value`";
	  
	map<string, double> const &components = solution.fitness().components();
	map<string, double>::const_iterator iter;
	stringstream values;
	
	values << "VALUES(" << solution.id() << ", " << currentIteration() << ", " << solution.fitness().value();
	
	for (iter = components.begin(); iter != components.end(); ++iter)
	{
		string norm = normalizeFitnessName(iter->first);
		
		q << ", `_" << norm << "`";
		values << ", " << iter->second;
	}
	
	q << ") " << values.str() << ")" << SQLite::Query::End();
}
