#include "webots.ih"

void Webots::respondFail() 
{
	map<string, double> fitness;
	respond(messages::worker::Response::Failed, fitness);
}
