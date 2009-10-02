#include "webots.ih"

void Webots::respond(map<string, double> const &fitness) 
{
	respond(messages::task::Response::Success, fitness);
}
