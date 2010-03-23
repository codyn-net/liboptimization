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

#include <jessevdk/base/base.hh>
#include <optimization/constants.hh>
#include <optimization/messages.hh>
#include <optimization/debug.hh>

using namespace std;
using namespace optimization;
using namespace jessevdk::base::signals;

/**
 * @class optimization::Discovery
 * @brief Optimization discovery
 *
 * This class implements a very simple discovery protocol used by the master
 * and worker process to be able to discovery each other. There are two
 * messages: Wakeup and Greeting. The workers will periodically send Greeting
 * messages (by default over multicast, see Constants::DiscoveryGroup). This
 * message contains the address description of the location of the worker, so
 * that when a master receives it, it knows how to connect to the worker.
 *
 * In addition, a master may send a Wakeup message requesting any workers to
 * send him a Greeting message. This way when a master is started, it can
 * immediately receive all the active workers without having to wait for them
 * to send there periodic greeting.
 *
 * The discovery protocol implements a namespace to seperate different groups
 * of workers and masters (see Namespace() and SetNamespace()). By default
 * a discovery object is in the anonymous namespace.
 *
 */

/**
 * @class optimization::Discovery::Info
 * @brief Discovery info
 *
 * Simple struct used in the discovery signals to provide information on
 * the connection string and host of the discovery request.
 *
 */

/**
 * @brief Check the discovery namespace (const).
 * @param ns the namespace to check
 *
 * Check if the specified namespace matches with the namespace set for this
 * discovery object.
 *
 * @return true if the namespaces match, false otherwise
 */
bool
Discovery::Data::CheckNamespace(string const &ns) const
{
	return (this->ns == ns);
}

/**
 * @brief Discovery constructor.
 *
 * Constructor.
 *
 * Create new discovery object.
 *
 */
Discovery::Discovery()
:
	UdpServer(Constants::DiscoveryGroup, Constants::DiscoveryPort)
{
	d_data = new Data();
	AddPrivateData(d_data);
}

/**
 * @brief Listen on the discovery address.
 *
 * Start listening on the discovery address.
 *
 * @return true if listening, false otherwise
 *
 */
bool
Discovery::Listen()
{
	bool ret = UdpServer::Listen();

	if (ret)
	{
		OnData().Add(*d_data, &Discovery::Data::OnDataHandler);
	}

	return ret;
}

/**
 * @brief The discovery namespace (const).
 *
 * Get the discovery namespace. The namespace is used to separate several
 * groups of master and worker processes.
 *
 * @return Description
 *
 */
string const &
Discovery::Namespace() const
{
	return d_data->ns;
}

/**
 * @brief Discovery data callback handler.
 * @param args data args
 *
 * Called when data is received on the discovery port.
 *
 */
void
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

		info.Host = args.Address.Host(true);

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
}

/**
 * @brief Set the discovery namespace.
 * @param ns the namespace
 *
 * Set the discovery namespace. The namespace is used to separate several
 * groups of master and worker processes.
 * @fn void optimization::Discovery::SetNamespace(std::string const &ns)
 */
void
Discovery::SetNamespace(string const &ns)
{
	d_data->ns = ns;
}

/**
 * @brief Greeting signal.
 *
 * Signal emitted when a greeting message was received.
 *
 * @return the signal object
 *
 */
Signal<Discovery::Info> &
Discovery::OnGreeting()
{
	return d_data->onGreeting;
}

/**
 * @brief OnWakeup signal
 *
 * Signal emitted when a wakeup message was received.
 *
 * @return the signal object
 *
 */
Signal<Discovery::Info> &
Discovery::OnWakeup()
{
	return d_data->onWakeup;
}
