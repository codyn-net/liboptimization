#include "discovery.ih"

bool Discovery::listen()
{
	bool ret = UdpServer::listen();

	if (ret)
	{
		onData().add(*d_data, &Discovery::Data::onDataHandler);
	}

	return ret;
}
