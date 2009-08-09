#include "optimizer.ih"

db::SQLite &Optimizer::db()
{
	return d_data->db;
}
