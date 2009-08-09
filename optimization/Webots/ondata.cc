#include "webots.ih"

bool Webots::onData(os::FileDescriptor::DataArgs &args) 
{
	vector<messages::worker::Request::Dispatch> request;
	vector<messages::worker::Request::Dispatch>::iterator iter;
	
	Messages::extract(args, request);
	
	for (iter = request.begin(); iter != request.end(); ++iter)
	{
		d_request = *iter;
		d_hasRequest = true;
		break;
	}
}
