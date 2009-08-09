#include "discovery.ih"

Discovery::Discovery()
:
	UdpServer(Constants::DiscoveryGroup, Constants::DiscoveryPort)
{
	d_data = new Data();
	addPrivateData(d_data);
}
