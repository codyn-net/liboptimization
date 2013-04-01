/*
 *  taskreader.cc - This file is part of liboptimization
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

#include "taskreader.hh"
#include <optimization/messages.hh>
#include <iostream>

using namespace std;
using namespace optimization;
using namespace optimization::messages;

struct TaskReader::PrivateData
{
	messages::task::Task task;
	std::map<std::string, std::string> settings;
	std::map<std::string, std::string> data;
	std::map<std::string, messages::task::Task::Parameter> parameters;
	bool taskRead;
};

/* Create new task reader.
 *
 * Create a new taskreader object.
 */
TaskReader::TaskReader()
{
	d = new PrivateData();
	d->taskRead = false;
}

/* Create new task reader for an input stream.
 * @stream the input stream to read from.
 *
 * Create a new task reader which starts reading the task from the specified
 * input stream. Note that reading the task is **blocking** until a task has
 * been read.
 */
TaskReader::TaskReader(std::istream &stream)
{
	d = new PrivateData();
	d->taskRead = false;

	ReadRequest(stream);
}

/* Default destructor. */
TaskReader::~TaskReader()
{
	delete d;
}

/* Read task from input stream.
 * @stream the input stream to read from.
 *
 * ReadRequest reads one task from the specified input stream. Note that this
 * call **blocks** until a task has been successfully read (or there was an error).
 * You would normally not call this method directly since it's automatically
 * called from the constructor.
 *
 * @return true if the request could be read, false otherwise.
 */
bool
TaskReader::ReadRequest(std::istream &stream)
{
	/* Read request from stdin */
	d->taskRead = false;

	task::Communication comm;

	// Keep reading until a correct message has been received (or end of stream)
	while (stream && !Messages::Extract(stream, comm))
	{
	}

	if (comm.type() == task::Communication::CommunicationTask)
	{
		ReadRequest(comm.task());
	}
	else
	{
		cerr << "** [TaskReader] Could not parse message from array" << endl;
	}

	return d->taskRead;
}

/* Read request from task description object.
 * @task the task.
 *
 * ReadRequest sets the task description directly from the task object. This
 * is used by subclasses who implement retrieving a task from something other
 * than a c++ input stream.
 *
 */
void
TaskReader::ReadRequest(messages::task::Task const &task)
{
	d->task = task;

	ReadSettings();
	ReadParameters();
	ReadData();

	d->taskRead = true;
}

void
TaskReader::ReadSettings()
{
	size_t num = d->task.settings_size();
	d->settings.clear();

	for (size_t i = 0; i < num; ++i)
	{
		messages::task::Task::KeyValue const &kv = d->task.settings(i);
		d->settings[kv.key()] = kv.value();
	}
}

void
TaskReader::ReadData()
{
	size_t num = d->task.data_size();
	d->data.clear();

	for (size_t i = 0; i < num; ++i)
	{
		messages::task::Task::KeyValue const &kv = d->task.data(i);
		d->data[kv.key()] = kv.value();
	}
}

void
TaskReader::ReadParameters()
{
	size_t num = d->task.parameters_size();
	d->parameters.clear();

	for (size_t i = 0; i < num; ++i)
	{
		task::Task::Parameter const &parameter = d->task.parameters(i);
		d->parameters[parameter.name()] = parameter;
	}
}

/* Get a task dispatcher setting by name.
 * @name the setting name.
 * @value the setting value return value.
 *
 * Get a dispatcher setting by <name>. <value> will be set to the value of
 * the setting <name> when the setting could be found. If the setting was not
 * present, then this method returns false. <value> may be nullptr.
 *
 * @return true if the setting could be found, false otherwise.
 */
bool
TaskReader::Setting(std::string const &name, std::string *value) const
{
	map<string, string>::const_iterator found = d->settings.find(name);

	if (found == d->settings.end())
	{
		return false;
	}

	if (value)
	{
		*value = found->second;
	}

	return true;
}

/* Check if a dispatcher setting exists.
 * @name the setting name.
 *
 * Setting checks if a dispatcher setting exists.
 *
 * @return true if the setting exists, false otherwise.
 */
bool
TaskReader::Setting(std::string const &name) const
{
	return Setting(name, 0);
}

/* Get a task parameter by name.
 * @name the parameter name.
 * @parameter the parameter value return value.
 *
 * Parmaeter gets a task parameter by <name>. <parameter> will be set to the value of
 * the parameter <name> when the parameter could be found. If the parameter was not
 * present, then this method returns false. <parameter> may be nullptr.
 *
 * If you only need to get the numeric value of the parameter, then use
 * <Parameter(std::string, double*)> instead.
 *
 * @return true if the parameter could be found, false otherwise.
 */
bool
TaskReader::Parameter(std::string const &name, task::Task::Parameter *parameter) const
{
	map<string, task::Task::Parameter>::const_iterator found = d->parameters.find(name);

	if (found == d->parameters.end())
	{
		return false;
	}

	if (parameter)
	{
		*parameter = found->second;
	}

	return true;
}

/* Get a task parameter value by name.
 * @name the parameter name.
 * @value the parameter value return value.
 *
 * Parameter gets a task parameter by <name>. <value> will be set to the value of
 * the parameter <name> when the parameter could be found. If the parameter was not
 * present, then this method returns false. <value> may be nullptr.
 *
 * @return true if the parameter could be found, false otherwise.
 */
bool
TaskReader::Parameter(std::string const &name, double *value) const
{
	task::Task::Parameter parameter;

	if (!Parameter(name, &parameter))
	{
		return false;
	}

	if (value)
	{
		*value = parameter.value();
	}

	return true;
}

/* Check if a parameter exists.
 * @name the parameter name.
 *
 * Parameter checks if a parameter with the name <name> exists.
 *
 * @return true if the parameter exists, false otherwise.
 */
bool
TaskReader::Parameter(std::string const &name) const
{
	return Parameter(name, static_cast<double *>(0));
}

/* Get a task data item by name.
 * @name the data item name.
 * @value the data value return value.
 *
 * Data gets a task data item by <name>. <value> will be set to the value of
 * the data item <name> when the data item could be found. If the data item was not
 * present, then this method returns false. <value> may be nullptr.
 *
 * @return true if the data item could be found, false otherwise.
 */
bool
TaskReader::Data(std::string const &name, std::string *value) const
{
	map<string, string>::const_iterator found = d->data.find(name);

	if (found == d->data.end())
	{
		return false;
	}

	if (value)
	{
		*value = found->second;
	}

	return true;
}

/* Check if a data item exists.
 * @name the data item name.
 *
 * Data checks if a data item exists.
 *
 * @return true if the data item exists, false otherwise.
 */
bool
TaskReader::Data(std::string const &name) const
{
	return Data(name, 0);
}

/* Get the task request.
 *
 * Task gets the task request. Note that this will only return a valid task
 * when a task has been successfully retrieved. Whether or not the task is
 * valid can be verified with <HasTask>.
 *
 * @return the task request
 */
optimization::messages::task::Task &
TaskReader::Task()
{
	return d->task;
}

/* Check whether a task has been successfully read.
 *
 * Check if a task has been successfully read. This is a convenience alias for
 * <HasTask>.
 *
 * @return true if a task was read, false otherwise.
 */
TaskReader::operator bool() const
{
	return d->taskRead;
}

/* Check whether a task has been successfully read.
 *
 * Check if a task has been successfully read.
 *
 * @return true if a task was read, false otherwise.
 */
bool
TaskReader::HasTask() const
{
	return d->taskRead;
}
