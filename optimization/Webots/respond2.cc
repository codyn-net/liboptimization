#include "webots.ih"

void Webots::respond(messages::worker::Response::Status status, map<string, double> const &fitness) 
{
	messages::worker::Response res;
	
	res.set_id(0);
	res.set_status(status);
	
	for (map<string, double>::const_iterator iter = fitness.begin(); iter != fitness.end(); ++iter)
	{
		messages::worker::Response::Fitness *f = res.add_fitness();
		f->set_name(iter->first);
		f->set_value(iter->second);
	}
	
	response(res);
}
