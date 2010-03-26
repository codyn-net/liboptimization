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
#include <iostream>
#include <optimization/messages.hh>
#include <iostream>

using namespace std;
using namespace optimization;
using namespace optimization::messages;

/**
 * @class optimization::TaskReader
 * @brief TaskReader class.
 *
 * TODO
 */

TaskReader::TaskReader()
:
	d_taskRead(false)
{
}

TaskReader::TaskReader(istream &stream)
:
	d_taskRead(false)
{
	ReadRequest(stream);
}

/**
 * @brief Read task task request from STDIN.
 *
 * Reads the task request from STDIN.
 *
 * @return true if the request could be read, false otherwise
 *
 */
bool
TaskReader::ReadRequest(istream &stream)
{
	/* Read request from stdin */
	size_t num;

	d_taskRead = false;

	if (!(stream >> num))
	{
		cerr << "** [TaskReader] Could not read message size" << endl;
		return false;
	}

	if (!stream.ignore(1, ' '))
	{
		cerr << "** [TaskReader] Invalid message header" << endl;
		return false;
	}

	char *s = new char[num + 1];
	bool ret = false;

	if (stream.read(s, num))
	{
		if (d_task.ParseFromArray(s, num))
		{
			ret = true;

			ReadSettings();
			ReadParameters();
			ReadData();
		}
		else
		{
			cerr << "** [TaskReader] Could not parse message from array" << endl;
		}
	}
	else
	{
		cerr << "** [TaskReader] Could not read message" << endl;
	}

	delete[] s;

	d_taskRead = ret;
	return ret;
}

void
TaskReader::ReadRequest(messages::task::Task const &task)
{
	d_task = task;

	ReadSettings();
	ReadParameters();
	ReadData();

	d_taskRead = true;
}

/**
 * @brief Read task settings.
 *
 * Reads the tasks settings from the request.
 *
 */
void
TaskReader::ReadSettings()
{
	size_t num = d_task.settings_size();
	d_settings.clear();

	for (size_t i = 0; i < num; ++i)
	{
		messages::task::Task::KeyValue const &kv = d_task.settings(i);
		d_settings[kv.key()] = kv.value();
	}
}

/**
 * @brief Read task data.
 *
 * Reads the tasks data from the request.
 *
 */
void
TaskReader::ReadData()
{
	size_t num = d_task.data_size();
	d_data.clear();

	for (size_t i = 0; i < num; ++i)
	{
		messages::task::Task::KeyValue const &kv = d_task.data(i);
		d_data[kv.key()] = kv.value();
	}
}

/**
 * @brief Read task parameters.
 *
 * Reads the tasks parameters from the request.
 *
 */
void
TaskReader::ReadParameters()
{
	size_t num = d_task.parameters_size();
	d_parameters.clear();

	for (size_t i = 0; i < num; ++i)
	{
		task::Task::Parameter const &parameter = d_task.parameters(i);
		d_parameters[parameter.name()] = parameter;
	}
}

/**
 * @brief Get task task setting (const).
 * @param key the setting key
 * @param value setting value return value
 *
 * Get a task setting from the task request.
 *
 * @return true if the setting could be found, false otherwise
 * @fn bool TaskReader::Setting(std::string const &key, std::string &value) const
 */
bool
TaskReader::Setting(string const &key, string &value) const
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
 * @brief Get task task parameter (const).
 * @param name the parameter name
 * @param value parameter return value
 *
 * Get a task parameter from the task request.
 *
 * @return true if the setting could be found, false otherwise
 * @fn bool TaskReader::Parameter(std::string const &key, double &value) const
 */
bool
TaskReader::Parameter(string const &name, task::Task::Parameter &parameter) const
{
	map<string, task::Task::Parameter>::const_iterator found = d_parameters.find(name);

	if (found == d_parameters.end())
	{
		return false;
	}

	parameter = found->second;
	return true;
}

/**
 * @brief Get task data (const).
 * @param key the data key
 * @param value data value return value
 *
 * Get a task data from the task request.
 *
 * @return true if the data could be found, false otherwise
 * @fn bool TaskReader::Data(std::string const &key, std::string &value) const
 */
bool
TaskReader::Data(string const &key, string &value) const
{
	map<string, string>::const_iterator found = d_data.find(key);

	if (found == d_data.end())
	{
		return false;
	}

	value = found->second;
	return true;
}

/**
 * @brief Get task task parameter (const).
 * @param name the parameter name
 * @param value parameter value return value
 *
 * Get a task parameter from the task request.
 *
 * @return true if the setting could be found, false otherwise
 * @fn bool TaskReader::Parameter(std::string const &key, double &value) const
 */
bool
TaskReader::Parameter(string const &name, double &value) const
{
	task::Task::Parameter parameter;

	if (!Parameter(name, parameter))
	{
		return false;
	}

	value = parameter.value();
	return true;
}

bool
TaskReader::Parameter(string const &name) const
{
	task::Task::Parameter parameter;

	return Parameter(name, parameter);
}

/**
 * @brief Check if task setting is set (const).
 * @param key setting key
 *
 * Check whether a task setting in the task request is set.
 *
 * @return true if the task setting is set, false otherwise
 * @fn bool TaskReader::Setting(std::string const &key) const
 */
bool
TaskReader::Setting(string const &key) const
{
	string dummy;
	return Setting(key, dummy);
}

/**
 * @brief Check if task data is set (const).
 * @param key data key
 *
 * Check whether a task data in the task request is set.
 *
 * @return true if the task data is set, false otherwise
 * @fn bool TaskReader::Data(std::string const &key) const
 */
bool
TaskReader::Data(string const &key) const
{
	string dummy;
	return Data(key, dummy);
}

/**
 * @brief Get the task request.
 *
 * Get the task request to be processed by the task.
 *
 * @return the task request
 *
 */
optimization::messages::task::Task &
TaskReader::Task()
{
	return d_task;
}

TaskReader::operator bool() const
{
	return d_taskRead;
}

bool
TaskReader::HasTask() const
{
	return d_taskRead;
}
