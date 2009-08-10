#include "optimizer.ih"

void Optimizer::log(base::Enum<LogType> const &type, string const &message)
{
	if (!d_data->db)
	{
		return;
	}
	
	d_data->db.query() << "INSERT INTO `log` (`time`, `type`, `message`) VALUES ("
	                   << time(0) << ", '"
	                   << string(type) << "', '"
	                   << SQLite::serialize(message) << "')"
	                   << SQLite::Query::end();
}
