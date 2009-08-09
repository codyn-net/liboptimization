#include "optimizer.ih"

void Optimizer::initialize(Parameters const &parameters, Boundaries const &boundaries, Fitness const &fitness)
{
	d_data = new Data();
	addPrivateData(d_data);

	d_data->maxIterations = 30;
	d_data->populationSize = 40;
	d_data->timeout = 0;
	d_data->seed = 0;

	d_data->settings.registerProperty("maxIterations", d_data->maxIterations);
	d_data->settings.registerProperty("populationSize", d_data->populationSize);
	d_data->settings.registerProperty("timeout", d_data->timeout);
	d_data->settings.registerProperty("seed", d_data->seed, *d_data, &Data::setSeed);
	
	setup(parameters, boundaries, fitness);
}
