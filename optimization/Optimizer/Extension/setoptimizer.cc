#include "extension.ih"

void Optimizer::Extension::setOptimizer(Optimizer const &optimizer)
{
	d_data->optimizer = optimizer.clone();
}
