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

#include <os/Environment/environment.hh>
#include <optimization/messages.hh>
#include <glibmm.h>
#include <base/Debug/debug.hh>

using namespace std;
using namespace optimization;

Webots *Webots::s_instance = 0;

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

	d_client.onData().add(*this, &Webots::OnData);
}

bool
Webots::HasRequest() const
{
	return d_hasRequest;
}

Webots &
Webots::Instance() 
{
	if (!s_instance)
	{
		s_instance = new Webots();
	}

	return *s_instance;
}

bool
Webots::OnData(os::FileDescriptor::DataArgs &args) 
{
	vector<messages::task::Task::Description> request;
	vector<messages::task::Task::Description>::iterator iter;

	Messages::Extract(args, request);

	for (iter = request.begin(); iter != request.end(); ++iter)
	{
		d_request = *iter;
		d_hasRequest = true;
		break;
	}
}

Webots::operator bool() const
{
	return d_client;
}

void
Webots::ReadSettings()
{
	size_t num = d_request.settings_size();

	for (size_t i = 0; i < num; ++i)
	{
		messages::task::Task::Description::KeyValue const &kv = d_request.settings(i);
		d_settings[kv.key()] = kv.value();
	}
}

optimization::messages::task::Task::Description &
Webots::Request()
{
	return d_request;
}

void
Webots::Respond(map<string, double> const &fitness) 
{
	Respond(messages::task::Response::Success, fitness);
}

void
Webots::Respond(messages::task::Response::Status  status, 
                map<string, double> const        &fitness) 
{
	messages::task::Response res;

	res.set_id(0);
	res.set_status(status);

	for (map<string, double>::const_iterator iter = fitness.begin(); iter != fitness.end(); ++iter)
	{
		messages::task::Response::Fitness *f = res.add_fitness();

		f->set_name(iter->first);
		f->set_value(iter->second);
	}

	Response(res);
}

void
Webots::RespondFail() 
{
	map<string, double> fitness;
	Respond(messages::task::Response::Failed, fitness);
}

void
Webots::Response(messages::task::Response &res)
{
	if (!d_client)
	{
		return;
	}

	// Send the response
	string serialized;

	if (Messages::Create(res, serialized))
	{
		d_client.write(serialized);
	}
}

bool
Webots::Setting(string const &key, 
                string       &value)
{
	// Make sure to wait for request first
	WaitForRequest();

	map<string, string>::const_iterator found = d_settings.find(key);

	if (found == d_settings.end())
	{
		return false;
	}

	value = found->second;
	return true;
}

bool
Webots::Setting(string const &key)
{
	string dummy;

	return Setting(key, dummy);
}

void
Webots::WaitForRequest()
{
	Glib::RefPtr<Glib::MainContext> ctx = Glib::MainContext::get_default();

	while (!HasRequest())
	{
		ctx->iteration(true);
	}

	ReadSettings();
}
