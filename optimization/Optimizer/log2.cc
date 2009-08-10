#include "optimizer.ih"

Optimizer::Logger Optimizer::log(base::Enum<LogType> const &type)
{
	return Optimizer::Logger(this, type);
}
