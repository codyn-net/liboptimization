#include "webots.ih"

void Webots::respondFail() 
{
	map<string, double> fitness;
	respond(messages::task::Response::Failed, fitness);
}
