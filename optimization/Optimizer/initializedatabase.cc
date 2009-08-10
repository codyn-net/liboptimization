#include "optimizer.ih"

void Optimizer::initializeDatabase()
{
	if (d_data->db || d_data->dataFilename == "")
	{
		return;
	}

	d_data->db = SQLite(d_data->dataFilename);
	SQLite &db = d_data->db;
	
	if (!db)
	{
		return;
	}
	
	db.begin();

	// Create and store optimizer settings
	db.query() << "CREATE TABLE IF NOT EXISTS `settings` ("
		       << "`name` TEXT, "
		       << "`value` TEXT)"
		       << SQLite::Query::End();

	db.query("DELETE FROM settings");
	vector<string> props = d_data->settings.properties();
	
	for (vector<string>::iterator iter = props.begin(); iter != props.end(); ++iter)
	{
		db.query() << "INSERT INTO settings (`name`, `value`) VALUES ('"
			       << SQLite::serialize(*iter) << "', '"
			       << SQLite::serialize(d_data->settings.property(*iter)) << "')"
		           << SQLite::Query::end();
	}
	
	// Store optimizer name
	db.query() << "INSERT INTO settings (`name`, `value`) VALUES ('optimizer', "
	           << "'" << SQLite::serialize(name()) << "')"
	           << SQLite::Query::end();

	// Create and store fitness settings
	db.query() << "CREATE TABLE IF NOT EXISTS `fitness` ("
		       << "`name` TEXT, "
		       << "`value` TEXT)"
		       << SQLite::Query::End();

	db.query("DELETE FROM fitness");
	props = d_data->fitness.settings().properties();
	
	for (vector<string>::iterator iter = props.begin(); iter != props.end(); ++iter)
	{
		db.query() << "INSERT INTO fitness (`name`, `value`) VALUES ('"
			       << SQLite::serialize(*iter) << "', '"
			       << SQLite::serialize(d_data->fitness.settings().property(*iter)) << "')"
		           << SQLite::Query::end();
	}
	
	// Create iteration table
	db.query() << "CREATE TABLE IF NOT EXISTS `iteration` ("
		       << "`iteration` INT PRIMARY KEY, "
		       << "`best_id` INT, `best_values` TEXT, "
		       << "`best_names` TEXT, "
		       << "`best_fitness` TEXT, "
		       << "`random_state` BLOB, "
		       << "`time` INT)"
		       << SQLite::Query::End();

	// Create solution table
	db.query() << "CREATE TABLE IF NOT EXISTS `solution` ("
		       << "`index` INT, "
		       << "`iteration` INT REFERENCES `iteration` (`iteration`), "
		       << "`values` TEXT, "
		       << "`value_names` TEXT, "
		       << "`fitness` DOUBLE, "
		       << "`fitness_raw` TEXT)"
		       << SQLite::Query::End();

	// Create and store boundaries
	db.query() << "CREATE TABLE IF NOT EXISTS `boundaries` ("
		       << "`name` TEXT, "
		       << "`min` DOUBLE, "
		       << "`max` DOUBLE)"
		       << SQLite::Query::End();

	db.query("DELETE FROM boundaries");
		
	optimization::Boundaries const &boundaries = d_data->boundaries;
	optimization::Boundaries::const_iterator iter;
	
	for (iter = boundaries.begin(); iter != boundaries.end(); ++iter)
	{
		db.query() << "INSERT INTO boundaries (`name`, `min`, `max`) VALUES ('"
			       <<  SQLite::serialize((*iter)->name) << "', "
			       << (*iter)->min << ", " 
			       << (*iter)->max << ")"
			       << SQLite::Query::end();
	}

	// Create and store  parameters
	db.query() << "CREATE TABLE IF NOT EXISTS `parameters` ("
		               << "`name` TEXT, "
		               << "`boundary` TEXT)"
		               << SQLite::Query::End();

	db.query("DELETE FROM parameters");
		
	optimization::Parameters const &parameters = d_data->parameters;
	optimization::Parameters::const_iterator it;
	
	for (it = parameters.begin(); it != parameters.end(); ++it)
	{
		db.query() << "INSERT INTO parameters (`name`, `boundary`) VALUES ('"
			       << SQLite::serialize((*it)->name) << "', '"
			       << (*it)->boundary.name << "')"
		           << SQLite::Query::end();
	}
	
	// Log table
	db.query() << "CREATE TABLE IF NOT EXISTS `log` ("
               << "`time` INT, "
	           << "`type` TEXT, "
	           << "`message` TEXT)"
	           << SQLite::Query::End();

	db.commit();
	
	vector<Cloneable<Extension> >::iterator ite;
	
	for (ite = d_data->extensions.begin(); ite != d_data->extensions.end(); ++ite)
	{
		(*ite)->initializeDatabase();
	}
}
