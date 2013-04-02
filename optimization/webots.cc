/*
 *  webots.cc - This file is part of liboptimization
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

#include "webots.hh"

#include <optimization/messages.hh>
#include <cstdio>

#ifdef MINGW
#include "webots_windows.hh"
#else
#include "webots_unix.hh"
#endif

#include "socketbuffer.hh"

using namespace std;
using namespace optimization;

struct Webots::PrivateData
{
	int socket;
	SocketStream stream;

	PrivateData(int s)
	:
		socket(s),
		stream(s)
	{
	}
};

Webots *Webots::s_instance = 0;

Webots::Webots()
:
	Dispatcher(true)
{
	d = new PrivateData(Connect());

	Initialize(d->stream, d->stream);

	if (HasTask() && !Setting("no-periodic-ping"))
	{
		SetupPeriodicPing();
	}
}

/* Default destructor. */
Webots::~Webots()
{
	if (d->socket != -1)
	{
		Disconnect(d->socket);
	}

	delete d;
}

/* Get webots dispatcher singleton instance.
 *
 * Instance gets the webots instance which allows interaction with the
 * optimization framework. See methods on the <optimization::Dispatcher> and
 * <optimization::TaskReader> base classes for more information on extracting
 * task information and sending back fitness values. Basic usage:
 *
 *     [code]
 *     // Get optimization instance
 *     optimization::Webots &optim = optimization::Webots::Instance();
 *     
 *     // See if we are in optimization mode
 *     if (optim)
 *     {
 *     
 *     }
 *
 * @return the webots optimization instance.
 */
Webots &
Webots::Instance()
{
	if (!s_instance)
	{
		s_instance = new Webots();
	}

	return *s_instance;
}

void
Webots::PeriodicPing()
{
	while (true)
	{
		sleep(15);

		// Send ping
		messages::task::Communication comm;

		comm.set_type(messages::task::Communication::CommunicationPing);
		comm.mutable_ping()->set_id(Task().id());

		string serialized;

		Messages::Write(comm, d->stream);
	}
}

void *
Webots::PeriodicPingThread(void *ptr)
{
	Webots *wb = (Webots *)ptr;
	wb->PeriodicPing();

	return 0;
}

