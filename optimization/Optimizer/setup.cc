#include "optimizer.ih"

void Optimizer::setup(Parameters const &parameters, Boundaries const &boundaries, Fitness const &fitness)
{
	d_data = new Data();
	addPrivateData(d_data);

	d_data->maxIterations = 30;
	d_data->populationSize = 40;
	d_data->seed = 0;

	d_data->state.settings.registerProperty("maxIterations", d_data->maxIterations);
	d_data->state.settings.registerProperty("populationSize", d_data->populationSize);
	d_data->state.settings.registerProperty("seed", d_data->seed, *d_data, &Data::setSeed);
	
	initialize(parameters, boundaries, fitness);
}
