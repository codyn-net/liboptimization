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

#ifdef MINGW
#include "webots_windows.hh"
#else
#include "webots_unix.hh"
#endif

using namespace std;
using namespace optimization;

struct SocketBuffer : public std::streambuf
{
	int socket;

	char *buffer;

	size_t contents_size;
	size_t buffer_size;

	SocketBuffer(int s)
	:
		socket(s)
	{
		buffer_size = 1024 * 1024;
		contents_size = 0;

		buffer = (char *)malloc(buffer_size);

		setg(buffer, buffer, buffer + contents_size);
	}

	int underflow()
	{
		if (buffer_size == contents_size)
		{
			buffer_size *= 2;

			// Make buffer larger
			buffer = (char *)realloc(buffer, buffer_size);
		}

		ssize_t n = ::recv(socket, buffer + contents_size, buffer_size - contents_size, 0);

		if (n <= 0)
		{
			return EOF;
		}

		size_t newcontents = contents_size + n;
		int ret = (int)*(buffer + contents_size);

		setg(buffer, buffer + contents_size, buffer + newcontents);
		contents_size = newcontents;

		return ret;
	}

	~SocketBuffer()
	{
		if (buffer)
		{
			free(buffer);
		}
	}
};

struct Webots::PrivateData
{
	int socket;
};

Webots *Webots::s_instance = 0;

Webots::Webots()
{
	d = new PrivateData();

	d->socket = Connect();

	if (d->socket == -1)
	{
		return;
	}

	SocketBuffer buffer(d->socket);
	istream stream(&buffer);

	if (!ReadRequest(stream))
	{
		return;
	}

	if (!Setting("no-periodic-ping"))
	{
		//Glib::Thread::create(sigc::mem_fun(*this, &Webots::PeriodicPing), false);
	}
}

Webots::~Webots()
{
	if (d->socket != -1)
	{
		Disconnect(d->socket);
	}

	delete d;
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
Webots::Respond(std::map<std::string, double> const &fitness)
{
	SetFitness(fitness);

	Dispatcher::WriteResponse();
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
	AddFitness("value", fitness);

	Dispatcher::WriteResponse();
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
Webots::Respond(double fitness, std::map<std::string, std::string> const &data)
{
	AddFitness("value", fitness);
	SetData(data);

	Dispatcher::WriteResponse();
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
Webots::Respond(std::map<std::string, double> const &fitness, std::map<std::string, std::string> const &data)
{
	SetFitness(fitness);
	SetData(data);

	Dispatcher::WriteResponse();
}

bool
Webots::WriteResponse(string const &s)
{
	if (d->socket == -1)
	{
		return false;
	}

	return Send(d->socket, (void *)s.c_str(), s.length(), 0) == (ssize_t)s.length();
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

		if (Messages::Create(comm, serialized))
		{
			Send(d->socket, (void *)serialized.c_str(), serialized.length(), 0);
		}
	}
}

void *
Webots::PeriodicPingThread(void *ptr)
{
	Webots *wb = (Webots *)ptr;
	wb->PeriodicPing();

	return 0;
}

