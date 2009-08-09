#include "webots.ih"

Webots::Webots()
:
	d_hasRequest(false)
{
	string path;
	
	// Get unix socket name from environment
	if (!os::Environment::variable("OPTIMIZATION_UNIX_SOCKET", path))
	{
		return;
	}
	
	Glib::init();
	
	// Open unix socket client
	d_client = network::Client::Unix(path);

	if (!d_client)
	{
		return;
	}
	
	d_client.onData().add(*this, &Webots::onData);
}
