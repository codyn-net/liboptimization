#include "optimizer.ih"

void Optimizer::save(Solution &solution)
{
	vector<double> fitness = solution.fitness().values();

	d_data->db.query() << "INSERT INTO solution ("
	                   << "`index`, `iteration`, `values`, `value_names`, "
	                   << "`fitness_raw`, `fitness`) VALUES ("
		               << solution.id() << ", "
		               << currentIteration() << ", '"
		               << SQLite::serialize(solution.parameters().values()) << "', '"
		               << SQLite::serialize(solution.parameters().names()) << "', '"
		               << SQLite::serialize(fitness) << "', "
		               << solution.fitness().value() << ")"
		               << SQLite::Query::end();
}
