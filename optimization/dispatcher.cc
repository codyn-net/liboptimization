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

struct Dispatcher::PrivateData
{
	ostream &output;
	messages::task::Response response;

	PrivateData(ostream &output);
};

Dispatcher::PrivateData::PrivateData(ostream &output)
:
	output(output)
{
}

/* Default constructor.
 *
 * The default constructor creates a new dispatcher instance using std::cin
 * and std::cout as the input and output streams. Use this constructor if you
 * are implementing a custom dispatcher process.
 */
Dispatcher::Dispatcher()
:
	TaskReader(cin)
{
	d = new PrivateData(cout);

	SetupResponse();
}

/* Streams constructor.
 * @stream the input stream to read the task from.
 * @output the output stream to write the response to.
 *
 * The streams constructor creates a new dispatcher instance using the provided
 * input and output streams. This can be useful if the task description and
 * dispatcher response have to be read/written from/to different locations than
 * the standard input/output.
 */
Dispatcher::Dispatcher(istream &stream, ostream &output)
:
	TaskReader(stream)
{
	d = new PrivateData(output);

	SetupResponse();
}

/* Lazy initialization constructor.
 * @lazyInit dummy parameter.
 *
 * The lazy initialization constructor is a special protected constructor which
 * can be used by subclasses, in conjunction with <Initialize> to initialize
 * the input and output streams of the dispatcher after construction.
 */
Dispatcher::Dispatcher(bool lazyInit)
{
}

/* Lazy initialization.
 * @stream the input stream.
 * @output the output stream.
 *
 * Initialize is used to lazily initialize the input and output streams of the
 * dispatcher. This only works in conjunction with the lazy initialization
 * constructor.
 */
void
Dispatcher::Initialize(istream &stream, ostream &output)
{
	if (!d)
	{
		d = new PrivateData(output);

		ReadRequest(stream);
		SetupResponse();
	}
}

/* Default destructor. */
Dispatcher::~Dispatcher()
{
	delete d;
}

void
Dispatcher::SetupResponse()
{
	if (!*this)
	{
		return;
	}

	messages::task::Task &t = Task();

	d->response.set_id(t.id());
	d->response.set_uniqueid(t.uniqueid());

	d->response.set_status(messages::task::Response::Failed);

	messages::task::Response::Failure *failure = d->response.mutable_failure();

	failure->set_type(messages::task::Response::Failure::NoResponse);
	failure->set_message("No response received");
}

/* Write response to output stream.
 *
 * WriteResponse writes the current response to the output stream. If you use
 * the <Respond> methods then <WriteResponse> will be automatically called.
 * If you however use <SetResponse>, <SetFitness>, <AddFitness>, <SetData> or
 * <AddData> manually, you will need to call <WriteResponse> to write the
 * resulting response to the output stream.
 *
 * @return true if the response was written successfully, false otherwise.
 */
bool
Dispatcher::WriteResponse()
{
	string serialized;

	messages::task::Communication comm;

	comm.set_type(messages::task::Communication::CommunicationResponse);
	*(comm.mutable_response()) = d->response;

	return Messages::Write(comm, d->output);
}

/* Set response.
 * @response the response.
 *
 * SetResponse sets the provided <response> object as the current response.
 * Only the fitness, data and failure fields of the response object are copied.
 * See <Respond> for more convenience methods to write a response directly.
 *
 * Don't forget to use <WriteResponse> to write the response to the output stream.
 */
void
Dispatcher::SetResponse(messages::task::Response const &response)
{
	d->response.set_status(response.status());

	*(d->response.mutable_fitness()) = response.fitness();
	*(d->response.mutable_data()) = response.data();

	if (response.has_failure())
	{
		*(d->response.mutable_failure()) = response.failure();
	}
}

/* Add fitness.
 * @name the fitness name.
 * @value the fitness value.
 *
 * AddFitness adds a single fitness value to the current response.
 * See <Respond> for more convenience methods to write a response directly.
 *
 * Don't forget to use <WriteResponse> to write the response to the output stream.
 */
void
Dispatcher::AddFitness(string const &name, double value)
{
	messages::task::Response_Fitness *fitness;

	d->response.set_status(messages::task::Response::Success);

	fitness = d->response.add_fitness();

	fitness->set_name(name);
	fitness->set_value(value);
}

/* Set fitness.
 * @fitness the fitness.
 *
 * SetFitness sets the current response fitness values. Any previously added
 * fitness values will be overridden.
 * See <Respond> for more convenience methods to write a response directly.
 *
 * Don't forget to use <WriteResponse> to write the response to the output stream.
 */
void
Dispatcher::SetFitness(map<string, double> const &fitness)
{
	map<string, double>::const_iterator iter;

	d->response.clear_fitness();

	for (iter = fitness.begin(); iter != fitness.end(); ++iter)
	{
		AddFitness(iter->first, iter->second);
	}
}

/* Add data.
 * @name the data name.
 * @value the data value.
 *
 * AddData adds a single data item to the current response.
 * See <Respond> for more convenience methods to write a response directly.
 *
 * Don't forget to use <WriteResponse> to write the response to the output stream.
 */
void
Dispatcher::AddData(string const &name, string const &value)
{
	messages::task::Response_KeyValue *data;

	d->response.set_status(messages::task::Response::Success);

	data = d->response.add_data();

	data->set_key(name);
	data->set_value(value);
}

/* Set data.
 * @data the data.
 *
 * SetData sets the current response data. Any previously added
 * data will be overridden.
 * See <Respond> for more convenience methods to write a response directly.
 *
 * Don't forget to use <WriteResponse> to write the response to the output stream.
 */
void
Dispatcher::SetData(map<string, string> const &data)
{
	map<string, string>::const_iterator iter;

	d->response.clear_data();

	for (iter = data.begin(); iter != data.end(); ++iter)
	{
		AddData(iter->first, iter->second);
	}
}

/* Write success response to the dispatcher.
 * @fitness the fitness.
 *
 * Write a success response. This is the most convenient way of writing a
 * response. The fitness is a map of fitness names to values. You can thus set
 * multiple fitness values if you have a multi objective fitness function (and
 * your optimizer supports this kind of fitness evaluation). This method
 * automatically calls <WriteResponse>.
 */
void
Dispatcher::Respond(std::map<std::string, double> const &fitness)
{
	SetFitness(fitness);

	WriteResponse();
}

/* Write success response to the dispatcher.
 * @fitness the fitness.
 *
 * Write a success response. This is the most convenient way of writing a
 * response. This sends a single fitness value with the name "value". This
 * method automatically calls <WriteResponse>.
 */
void
Dispatcher::Respond(double fitness)
{
	AddFitness("value", fitness);

	WriteResponse();
}

/* Write success response to the dispatcher with additional data.
 * @fitness the fitness.
 * @data additional data.
 *
 * Write a success response with additional data. This is the most convenient
 * way of writing a response. This sends a single fitness value with the name
 * "value". The provided <data> is a map of string keys to string values which
 * gets stored along with the solution. This method automatically calls
 * <WriteResponse>.
 */
void
Dispatcher::Respond(double fitness, std::map<std::string, std::string> const &data)
{
	AddFitness("value", fitness);
	SetData(data);

	WriteResponse();
}

/* Write success response to the dispatcher with additional data.
 * @fitness the fitness.
 * @data additional data.
 *
 * Write a success response with additional data. This is the most convenient
 * way of writing a response. The fitness is a map of fitness names to values.
 * You can thus set multiple fitness values if you have a multi objective
 * fitness function (and your optimizer supports this kind of fitness
 * evaluation).
 *
 * The provided <data> is a map of string keys to string values which gets
 * stored along with the solution. This method automatically calls
 * <WriteResponse>.
 */
void
Dispatcher::Respond(std::map<std::string, double> const &fitness, std::map<std::string, std::string> const &data)
{
	SetFitness(fitness);
	SetData(data);

	WriteResponse();
}

