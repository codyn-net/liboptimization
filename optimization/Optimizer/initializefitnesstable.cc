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

	Fitness &fit = d_data->solutions[0]->fitness();
	map<string, double> const &components = fit.components();
	map<string, double>::const_iterator iter;
	
	for (iter = components.begin(); iter != components.end(); ++iter)
	{
		string norm = normalizeFitnessName(iter->first);
		q << ", `_" << norm << "` DOUBLE";
	}
	
	q << ")" << SQLite::Query::End();
}
