#include "optimizer.ih"

void Optimizer::setDataFilename(string const &filename)
{
	d_data->dataFilename = filename;
	
	if (filename != "" && !d_data->db)
	{
		initializeDatabase();
	}
}
