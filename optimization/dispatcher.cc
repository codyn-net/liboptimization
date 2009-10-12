/*
 *  dispatcher.cc - This file is part of liboptimization
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

#include "dispatcher.hh"
#include <iostream>
#include <optimization/messages.hh>

using namespace std;
using namespace optimization;
using namespace optimization::messages;

Glib::RefPtr<Glib::MainLoop> 
Dispatcher::Main() 
{
	return d_main;
}

bool
Dispatcher::ReadRequest() 
{
	/* Read request from stdin */
	size_t num;
	
	if (!(cin >> num))
	{
		cerr << "** [Dispatcher] Could not read message size" << endl;
		return false;
	}
	
	if (!cin.ignore(1, ' '))
	{
		cerr << "** [Dispatcher] Invalid message header" << endl;
		return false;
	}
	
	char *s = new char[num + 1];
	bool ret = false;
	
	if (cin.read(s, num))
	{		
		if (d_request.ParseFromArray(s, num))
		{
			ret = true;
			ReadSettings();
		}
		else
		{
			cerr << "** [Dispatcher] Could not parse message from array" << endl;
		}
	}
	else
	{
		cerr << "** [Dispatcher] Could not read message" << endl;
	}
	
	delete[] s;
	return ret;
}

void
Dispatcher::ReadSettings()
{
	size_t num = d_request.settings_size();
	
	for (size_t i = 0; i < num; ++i)
	{
		messages::task::Task::Description::KeyValue const &kv = d_request.settings(i);
		d_settings[kv.key()] = kv.value();
	}
}

bool
Dispatcher::Run() 
{
	Glib::init();
	
	if (!ReadRequest())
	{
		cerr << "** [Dispatcher] Invalid dispatch request" << endl;
		return false;
	}
	
	if (UseMainLoop())
	{
		d_main = Glib::MainLoop::create();
	}
	
	if (!RunSolution())
	{
		return false;
	}
	
	if (d_main)
	{
		d_main->run();
	}

	return true;
}

bool
Dispatcher::Setting(string const &key, string &value) const
{
	map<string, string>::const_iterator found = d_settings.find(key);

	if (found == d_settings.end())
	{
		return false;
	}

	value = found->second;
	return true;
}

bool
Dispatcher::Setting(string const &key) const
{
	string dummy;
	return Setting(key, dummy);
}

bool
Dispatcher::UseMainLoop() const
{
	return true;
}

bool
Dispatcher::WriteResponse(messages::task::Response &response) 
{
	string serialized;

	if (Messages::Create(response, serialized))
	{
		cout.write(serialized.c_str(), serialized.length());
		cout.flush();
		
		return true;
	}
	else
	{
		return false;
	}
}

optimization::messages::task::Task::Description &
Dispatcher::Request()
{
	return d_request;
}
