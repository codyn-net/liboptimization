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

/**
 * @class optimization::Webots
 * @brief Convenience optimization class for webots controllers
 *
 * The optimization::Webots class is a convenient class for evaluating
 * optimization solutions in webots. It is used in conjunction with the
 * webots dispatcher. Internally, the webots dispatcher sets up a communication
 * channel on which it sends the task request and listens for a response. This
 * class makes it easy to read that request and to send a response back from
 * your webots controller.
 *
 * The class is a singleton from which you can get an instance using Instance().
 * A basic use of the class is the following:
 * \code
 * optimiation::Webots &request = optimization::Webots::Instance();
 *
 * // See if we are in optimization mode
 * if (request)
 * {
 *     request.WaitForRequest();
 *
 *     // Read parameters, setup your controller
 * }
 * \endcode
 *
 * You can read additional settings as supplied in for instance a job xml file,
 * using Setting(). For instance, if you want to have your simulation run a
 * certain amount of time while measuring the performance of your robot, you
 * could add a MaximumTime setting, and read it using Setting(). Then after
 * running the simulation for that amount of time, use Respond() to send back
 * the fitness of the simulation and quit the simulation.
 */

Webots *Webots::s_instance = 0;

/**
 * @brief Default constructor.
 *
 * Constructor.
 *
 * The default constructor.
 *
 */
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

/**
 * @brief Check whether a request has been received (const).
 *
 * Check whether a dispatcher task request has been received.
 *
 * @return: true if a request has been received, false otherwise
 *
 */
bool
Webots::HasRequest() const
{
	return d_hasRequest;
}

/**
 * @brief Get webots dispatcher singleton instance.
 *
 * Get the webots dispatcher singleton instance.
 *
 * @return: the webots dispatcher instance
 *
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

/**
 * @brief Data received callback.
 * @param args data args
 *
 * Called when data has been received.
 *
 */
void
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

/**
 * @brief Get dispatcher validity (const).
 *
 * Get whether there is a connection with the webots dispatcher process. This
 * can be very useful if you want to test your webots controller. You can use
 * this function to see if you are in optimization mode or not, and setup
 * your controller accordingly.
 *
 * @return: true if there is a connection with the webots dispatcher process,
 * false otherwise
 *
 */
Webots::operator bool() const
{
	return d_client;
}

/**
 * @brief Read settings.
 *
 * Read settings.
 *
 */
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

/**
 * @brief Get the dispatcher task request.
 *
 * Get the dispatcher task request. Make sure to call WaitForRequest() before
 * calling this function to ensure the request is received.
 *
 * @return: the dispatcher task request
 *
 */
optimization::messages::task::Task::Description &
Webots::Request()
{
	return d_request;
}

/**
 * @brief Write success response to the dispatcher.
 * @param fitness the solution fitness
 *
 * Write a success response to the dispatcher. This is the most convenient way
 * of writing a response back to the dispatcher.
 * \fn void Webots::Respond(std::map<std::string, double> const &fitness)
 */
void
Webots::Respond(map<string, double> const &fitness) 
{
	Respond(messages::task::Response::Success, fitness);
}

/**
 * @brief Write fitness response to the dispatcher.
 * @param status the response status
 * @param fitness the fitness
 *
 * Write a response back to the dispatcher. Consider using Respond(std::map<std::string, double> const &fitness) which automatically sets the status to Success.
 * \fn void Webots::Respond(messages::task::Response::Status status, std::map<std::string, double> const &fitness)
 */
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

/**
 * @brief Write a fail response to the dispatcher.
 *
 * Write a fail response back to the dispatcher. You can use this to indicate
 * a failure in trying to execute the task. Note that by default, the master
 * process will try to reschedule failed tasks a number of times. Failing a
 * task should therefore be due to things like running out of resources, or
 * general crashes.
 *
 * If you just want to respond a low fitness (if your robot fell over for
 * instance), consider using Respond() with a zero fitness.
 *
 */
void
Webots::RespondFail() 
{
	map<string, double> fitness;
	Respond(messages::task::Response::Failed, fitness);
}

/**
 * @brief Write a response to the dispatcher.
 * @param res the response
 *
 * Write a response back to the dispatcher. This is a low level function and
 * you need to create the response object yourself (and make sure it's valid).
 * You can also use a higher level function (Respond() or RespondFail()).
 *
 */
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

/**
 * @brief Get dispatcher setting.
 * @param key setting key
 * @param value setting value return value
 *
 * Get a dispatcher setting.
 *
 * @return: true if the setting was found, false otherwise
 * \fn bool Webots::Setting(std::string const &key, std::string &value)
 */
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

/**
 * @brief Check if a dispatcher setting is set.
 * @param key setting key
 *
 * Check whether a dispatcher setting is set.
 *
 * @return: true if the setting is set, false otherwise
 * \fn bool Webots::Setting(std::string const &key)
 */
bool
Webots::Setting(string const &key)
{
	string dummy;

	return Setting(key, dummy);
}

/**
 * @brief Wait for request from dispatcher.
 *
 * Wait for a task request from the webots dispatcher. You should always wait
 * for the request to arrive before doing anything.
 *
 */
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
