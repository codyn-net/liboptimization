/*
 *  discovery.cc - This file is part of liboptimization
 *
 *  Copyright (C) 2009 - Jesse van den Kieboom
 *
 * This library is free software; you can redistribute it and/or modify it 
 * under the terms of the GNU Lesser General Public License as published by the 
 * Free Software Foundation; either version 2.1 of the License, or (at your 
 * option) any later version.
 * 
 * This library is distributed in the hope that it will be useful, but WITHOUT 
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or 
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License 
 * for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License 
 * along with this library; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA 
 */

#include "discovery.hh"

#include <base/base.hh>
#include <optimization/constants.hh>
#include <optimization/messages.hh>

using namespace std;
using namespace optimization;
using namespace base::signals;

bool
Discovery::Data::CheckNamespace(string const &ns) const
{
	return (this->ns == ns);
}

Discovery::Discovery()
:
	UdpServer(Constants::DiscoveryGroup, Constants::DiscoveryPort)
{
	d_data = new Data();
	addPrivateData(d_data);
}

bool
Discovery::Listen()
{
	bool ret = UdpServer::listen();

	if (ret)
	{
		onData().add(*d_data, &Discovery::Data::OnDataHandler);
	}

	return ret;
}

string const &
Discovery::Namespace() const
{
	return d_data->ns;
}

bool
Discovery::Data::OnDataHandler(UdpServer::DataArgs &args) 
{
	vector<messages::discovery::Discovery> discovery;
	vector<messages::discovery::Discovery>::iterator iter;
	
	Messages::Extract(args, discovery);
	
	for (iter = discovery.begin(); iter != discovery.end(); ++iter)
	{
		messages::discovery::Discovery &gr = *iter;
		Info info;
		
		if (!CheckNamespace(gr.has_namespace_() ? gr.namespace_() : ""))
		{
			continue;
		}

		info.Host = args.address.host(true);

		if (gr.type() == messages::discovery::Discovery::TypeGreeting)
		{
			info.Connection = gr.greeting().connection();

			debug_worker << "Received greeting: " << info.Connection << endl;
			onGreeting(info);
		}
		else if (gr.type() == messages::discovery::Discovery::TypeWakeup)
		{
			info.Connection = gr.wakeup().connection();
			
			debug_worker << "Received wakeup: " << info.Connection << endl;
			onWakeup(info);
		}		
	}
	
	return false;
}

void
Discovery::SetNamespace(string const &ns)
{
	d_data->ns = ns;
}

Signal<Discovery::Info> &
Discovery::OnGreeting()
{
	return d_data->onGreeting;
}

Signal<Discovery::Info> &
Discovery::OnWakeup()
{
	return d_data->onWakeup;
}
