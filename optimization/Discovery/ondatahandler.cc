#include "discovery.ih"

bool Discovery::Data::onDataHandler(UdpServer::DataArgs &args) 
{
	vector<messages::discovery::Discovery> discovery;
	vector<messages::discovery::Discovery>::iterator iter;
	
	Messages::extract(args, discovery);
	
	for (iter = discovery.begin(); iter != discovery.end(); ++iter)
	{
		messages::discovery::Discovery &gr = *iter;
		Info info;
		
		if (!checkNs(gr.has_namespace_() ? gr.namespace_() : ""))
		{
			continue;
		}

		info.host = args.address.host(true);

		if (gr.type() == messages::discovery::Discovery::GREETING)
		{
			info.connection = gr.greeting().connection();

			debug_worker << "Received greeting: " << info.connection << endl;
			onGreeting(info);
		}
		else if (gr.type() == messages::discovery::Discovery::WAKEUP)
		{
			info.connection = gr.wakeup().connection();
			
			debug_worker << "Received wakeup: " << info.connection << endl;
			onWakeup(info);
		}		
	}
	
	return false;
}
