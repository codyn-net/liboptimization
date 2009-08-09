#include "parameters.ih"

Parameters::operator vector<double>() const
{
	return values();
}
