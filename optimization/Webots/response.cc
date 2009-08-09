#include "webots.ih"

void Webots::response(messages::worker::Response &res) 
{
	if (!d_client)
	{
		return;
	}
	
	// Send the response
	string serialized;

	if (Messages::create(res, serialized))
	{
		d_client.write(serialized);
	}
}
