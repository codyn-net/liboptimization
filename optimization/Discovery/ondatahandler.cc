/*
 *  ondatahandler.cc - This file is part of liboptimization
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

		if (gr.type() == messages::discovery::Discovery::TypeGreeting)
		{
			info.connection = gr.greeting().connection();

			debug_worker << "Received greeting: " << info.connection << endl;
			onGreeting(info);
		}
		else if (gr.type() == messages::discovery::Discovery::TypeWakeup)
		{
			info.connection = gr.wakeup().connection();
			
			debug_worker << "Received wakeup: " << info.connection << endl;
			onWakeup(info);
		}		
	}
	
	return false;
}
