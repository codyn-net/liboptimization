#include "webots.ih"

optimization::messages::worker::Request::Dispatch &Webots::request() 
{
	return d_request;
}
