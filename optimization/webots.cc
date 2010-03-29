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
#include <glibmm.h>

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
 * optimization::Webots &optinst = optimization::Webots::Instance();
 *
 * // See if we are in optimization mode
 * if (optinst)
 * {
 *     optinst.WaitForRequest();
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
 *
 * Use Request() to get the optimization::messages::task::Task_Description
 * object to get the particular parameters and boundaries for the task that
 * has to be executed.
 *
 * If you want to send additional data back to the optimizer, you can use
 * one of the Respond() functions that accepts an additional map of string key
 * values. The optimizer will save this additional data so you can extract
 * it later.
 *
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
{
	string path;

	Glib::thread_init();

	// Get unix socket name from environment
	if (!jessevdk::os::Environment::Variable("OPTIMIZATION_UNIX_SOCKET", path))
	{
		return;
	}

	Glib::init();

	// Open unix socket client
	d_client = jessevdk::network::Client::Unix(path);

	if (!d_client)
	{
		return;
	}

	d_client.OnData().Add(*this, &Webots::OnData);
	WaitForRequest();

	if (*this && !Setting("no-periodic-ping"))
	{
		Glib::Thread::create(sigc::mem_fun(*this, &Webots::PeriodicPing), false);
	}
}

/**
 * @brief Get webots dispatcher singleton instance.
 *
 * Get the webots dispatcher singleton instance.
 *
 * @return the webots dispatcher instance
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
Webots::OnData(jessevdk::os::FileDescriptor::DataArgs &args)
{
	vector<messages::task::Communication> request;
	vector<messages::task::Communication>::iterator iter;

	Messages::Extract(args, request);

	if (request.size() != 0)
	{
		ReadRequest(request[0].task());
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
 * @return true if there is a connection with the webots dispatcher process,
 * false otherwise
 *
 */
Webots::operator bool() const
{
	return d_client;
}

/**
 * @brief Write success response to the dispatcher.
 * @param fitness the solution fitness
 *
 * Write a success response to the dispatcher. This is the most convenient way
 * of writing a response back to the dispatcher. The fitness is a map of
 * fitness names to values. You can thus set multiple fitness values if you
 * have a multi objective fitness function (and your optimizer supports this
 * kind of fitness evaluation).
 *
 * @fn void Webots::Respond(std::map<std::string, double> const &fitness)
 */
void
Webots::Respond(map<string, double> const &fitness)
{
	map<string, string> data;
	Respond(fitness, data);
}

/**
 * @brief Write success response to the dispatcher.
 * @param fitness the solution fitness
 *
 * Write a success response to the dispatcher. This is the most convenient way
 * of writing a response back to the dispatcher. This sends a single fitness
 * value, if you want to send multiple fitness values, you can use:
 * void Webots::Response(std::map<std::string, double> const &fitness)
 *
 */
void
Webots::Respond(double fitness)
{
	map<string, string> data;
	Respond(fitness, data);
}

/**
 * @brief Write fitness response to the dispatcher.
 * @param status the response status
 * @param fitness the fitness
 *
 * Write a response back to the dispatcher. Consider using Respond(std::map<std::string, double> const &fitness) which automatically sets the status to Success.
 * @fn void Webots::Respond(messages::task::Response::Status status, std::map<std::string, double> const &fitness)
 */
void
Webots::Respond(messages::task::Response::Status  status,
                map<string, double> const        &fitness)
{
	map<string, string> data;
	Respond(status, fitness, data);
}

/**
 * @brief Write success response to the dispatcher with additional data.
 * @param fitness the solution fitness
 * @param data additional data
 *
 * Write a success response to the dispatcher with additional data.
 * This is the most convenient way
 * of writing a response back to the dispatcher. This sends a single fitness
 * value, if you want to send multiple fitness values, you can use:
 * void Webots::Response(std::map<std::string, double> const &fitness, std::map<std::string, std::string> const &data)
 *
 * @fn void Webots::Respond(double fitness, std::map<std::string, std::string> const &data)
 */
void
Webots::Respond(double fitness, std::map<string, string> const &data)
{
	map<string, double> fitnessmap;
	fitnessmap["value"] = fitness;

	Respond(fitnessmap, data);
}

/**
 * @brief Write success response to the dispatcher with additional data.
 * @param fitness the solution fitness
 * @param data additional data
 *
 * Write a success response to the dispatcher with additional data.
 * This is the most convenient way
 * of writing a response back to the dispatcher. The fitness is a map of
 * fitness names to values. You can thus set multiple fitness values if you
 * have a multi objective fitness function (and your optimizer supports this
 * kind of fitness evaluation).
 *
 * @fn void Webots::Respond(std::map<std::string, double> const &fitness, std::map<std::string, std::string> const &data)
 */
void
Webots::Respond(std::map<std::string, double> const &fitness, std::map<string, string> const &data)
{
	Respond(messages::task::Response::Success, fitness, data);
}

/**
 * @brief Write fitness response to the dispatcher with additional data.
 * @param status the response status
 * @param fitness the fitness
 * @param data additional data
 *
 * Write a response back to the dispatcher with some additional data. Consider
 * using
 * Respond(std::map<std::string, double> const &fitness, std::map<std::string, std::string> const &data)
 * which automatically sets the status to Success.
 *
 * @fn void Webots::Respond(messages::task::Response::Status status, std::map<std::string, double> const &fitness, std::map<std::string, std::string> const &data)
 */
void
Webots::Respond(messages::task::Response::Status status, std::map<std::string, double> const &fitness, std::map<string, string> const &data)
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

	for (map<string, string>::const_iterator iter = data.begin(); iter != data.end(); ++iter)
	{
		messages::task::Response::KeyValue *d = res.add_data();

		d->set_key(iter->first);
		d->set_value(iter->second);
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
	messages::task::Communication comm;
	comm.set_type(messages::task::Communication::CommunicationResponse);

	*(comm.mutable_response()) = res;
	string serialized;

	if (Messages::Create(comm, serialized))
	{
		d_client.Write(serialized);
	}
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

	if (!d_client)
	{
		return;
	}

	while (!HasTask())
	{
		ctx->iteration(true);
	}
}

void
Webots::PeriodicPing()
{
	while (true)
	{
		sleep(20);

		// Send ping
		messages::task::Communication comm;

		comm.set_type(messages::task::Communication::CommunicationPing);
		comm.mutable_ping()->set_id(Task().id());

		string serialized;

		if (Messages::Create(comm, serialized))
		{
			d_client.Write(serialized);
		}
	}
}
