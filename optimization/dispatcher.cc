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

/**
 * @class optimization::Dispatcher
 * @brief Main dispatcher class.
 *
 * The dispatcher class is the main class that drives the dispatcher process.
 * It is mostly a convenience class that does the boring work such as reading
 * the dispatcher task request and writing a response message back to the
 * worker process.
 *
 * If you want to implement your own dispatcher, you should subclass the
 * Dispatcher class. You need to implement at least one method RunTask()
 * which job it is to evaluate the parameters supplied to the dispatcher in
 * the task request (Request()).
 *
 * There are two main modes of operation. If you can evaluate the solution
 * synchronously, you can simply implement RunTask() and call 
 * WriteResponse() with a response message. In this case you would override
 * UseMainLoop() to return FALSE.
 *
 * The second mode of operation is to use a glib main loop to handle some IO
 * asynchronously (you can use this for instance if you want to launch another
 * process that should handle the request, like the webots dispatcher). In this
 * case, you implement RunTask() to start some asynchronous process using
 * the main loop. A main loop will be created by default. If you at some point
 * get some result, you call WriteResponse() and quit the main loop.
 */

/**
 * @brief Run the dispatcher task request
 *
 * Main function that evaluates the dispatcher task request. Subclasses are
 * required to implement this function. They should either call WriteResponse()
 * with the response (and override UseMainLoop() to return false), or setup 
 * some asynchronous action and use the main loop (UseMainLoop()) to write a 
 * response at a later time.
 *
 * @return false if the request was invalid, true otherwise
 * @fn bool Dispatcher::RunTask()
 */

/**
 * @brief The glib main loop.
 *
 * Get the glib main loop for this dispatcher. The main loop will only be
 * created if UseMainLoop returns TRUE.
 *
 * @return the glib main loop
 *
 */
Glib::RefPtr<Glib::MainLoop> 
Dispatcher::Main() 
{
	return d_main;
}

/**
 * @brief Read dispatcher task request from STDIN.
 *
 * Reads the dispatcher request from STDIN.
 *
 * @return true if the request could be read, false otherwise
 *
 */
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

/**
 * @brief Read dispatcher settings.
 *
 * Reads the dispatchers settings from the request.
 *
 */
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

/**
 * @brief Dispatcher main loop.
 *
 * The dispatcher main loop. A dispatcher executable should instantiate a
 * dispatcher object and call this function. It will first read the task
 * request from STDIN. Then it calls RunTask and if needed will start a
 * glib main loop (this can be used for asynchronous dispatching).
 *
 * @return true if the dispatch was successfull, false otherwise
 *
 */
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
	
	if (!RunTask())
	{
		return false;
	}
	
	if (d_main)
	{
		d_main->run();
	}

	return true;
}

/**
 * @brief Get dispatcher task setting (const).
 * @param key the setting key
 * @param value setting value return value
 *
 * Get a dispatcher setting from the task request.
 *
 * @return true if the setting could be found, false otherwise
 * @fn bool Dispatcher::Setting(std::string const &key, std::string &value) const
 */
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

/**
 * @brief Check if dispatcher setting is set (const).
 * @param key setting key
 *
 * Check whether a dispatcher setting in the task request is set.
 *
 * @return true if the dispatcher setting is set, false otherwise
 * @fn bool Dispatcher::Setting(std::string const &key) const
 */
bool
Dispatcher::Setting(string const &key) const
{
	string dummy;
	return Setting(key, dummy);
}

/**
 * @brief Whether a main loop should be run (const).
 *
 * Get whether a main loop should be run after RunTask is called. 
 * Subclasses can override this if they do not need a main loop. The default
 * is TRUE.
 *
 * @return true if the dispatcher needs a main loop, false otherwise
 *
 */
bool
Dispatcher::UseMainLoop() const
{
	return true;
}

/**
 * @brief Write response.
 * @param response the response to write
 *
 * Write a response back to the worker process.
 *
 * @return true if the response was written, false otherwise
 *
 */
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

/**
 * @brief Get the task request.
 *
 * Get the task request to be processed by the dispatcher.
 *
 * @return the task request
 *
 */
optimization::messages::task::Task::Description &
Dispatcher::Request()
{
	return d_request;
}