#include "optimizer.ih"

void Optimizer::initializeFitnessTable()
{
	if (!d_data->db || d_data->solutions.size() == 0)
	{
		return;
	}
	
	SQLite::Query q = d_data->db.query();
	
	q << "CREATE TABLE IF NOT EXISTS `fitness` ("
	  << "`iteration` INT, "
	  << "`index` INT, "
	  << "`value` DOUBLE";

	Fitness::Values const &fitness = d_data->solutions[0]->fitness();
	Fitness::Values::const_iterator iter;
	
	for (iter = fitness.begin(); iter != fitness.end(); ++iter)
	{
		string norm = normalizeFitnessName(iter->first);
		q << ", `_" << norm << "` DOUBLE";
	}
	
	q << ")" << SQLite::Query::End();
}
