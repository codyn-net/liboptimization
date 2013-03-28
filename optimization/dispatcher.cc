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

Dispatcher::Dispatcher()
:
	TaskReader(cin)
{
	d = new PrivateData(cout);

	SetupResponse();
}

Dispatcher::Dispatcher(std::istream &stream, std::ostream &output)
:
	TaskReader(stream)
{
	d = new PrivateData(output);

	SetupResponse();
}

Dispatcher::~Dispatcher()
{
	delete d;
}

bool
Dispatcher::ReadRequest(istream &stream)
{
	bool ret;

	ret = TaskReader::ReadRequest(stream);

	SetupResponse();

	return ret;
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

bool
Dispatcher::WriteResponse()
{
	string serialized;

	messages::task::Communication comm;

	comm.set_type(messages::task::Communication::CommunicationResponse);
	*(comm.mutable_response()) = d->response;

	if (Messages::Create(comm, serialized))
	{
		WriteResponse(serialized);
		return true;
	}
	else
	{
		return false;
	}
}

bool
Dispatcher::WriteResponse(string const &s)
{
	d->output.write(s.c_str(), s.length());

	if (!d->output)
	{
		return false;
	}

	d->output.flush();
	return true;
}

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

void
Dispatcher::AddFitness(string const &name, double value)
{
	messages::task::Response_Fitness *fitness;

	d->response.set_status(messages::task::Response::Success);

	fitness = d->response.add_fitness();

	fitness->set_name(name);
	fitness->set_value(value);
}

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

void
Dispatcher::AddData(string const &name, string const &value)
{
	messages::task::Response_KeyValue *data;

	d->response.set_status(messages::task::Response::Success);

	data = d->response.add_data();

	data->set_key(name);
	data->set_value(value);
}

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
