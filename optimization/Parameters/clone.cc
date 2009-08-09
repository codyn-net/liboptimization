#include "parameters.ih"

Parameters *Parameters::clone() const
{
	return new Parameters(*this);
}
