#include "optimizer.ih"

string Optimizer::normalizeFitnessName(string const &name)
{
	return String(name).replace("`", "").replace("'", "").replace("\"", "");
}
