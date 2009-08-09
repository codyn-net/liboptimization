#include "parameters.ih"

Parameters *Parameters::copy() const
{
	return new Parameters(begin(), end());
}
