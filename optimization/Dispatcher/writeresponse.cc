#include "dispatcher.ih"

bool Dispatcher::writeResponse(messages::task::Response &response) 
{
	string serialized;

	if (Messages::create(response, serialized))
	{
		cout.write(serialized.c_str(), serialized.length());
		cout.flush();
		
		return true;
	}
	else
	{
		return false;
	}
}
