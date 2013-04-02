/*
 *  taskreader.hh - This file is part of liboptimization
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

#ifndef __OPTIMIZATION_TASK_READER_H__
#define __OPTIMIZATION_TASK_READER_H__

#include <optimization/messages/task.pb.h>
#include <iosfwd>

namespace optimization
{
	/* Task reader class.
	 *
	 * TaskReader is a class which reads a task specification, encoded
	 * using protobuf, from a C++ input stream (for example std::cin) and
	 * provides convienient methods for accessing parameters and settings.
	 *
	 * If you are writing a custom dispatcher, please see the <Dispatcher>
	 * class which also provides writing responses.
	 */
	class TaskReader
	{
		struct PrivateData;

		PrivateData *d;

		public:
			TaskReader();
			TaskReader(std::istream &stream);
			virtual ~TaskReader();

			messages::task::Task &Task();

			virtual bool Setting(std::string const &name, std::string *value) const;
			virtual bool Setting(std::string const &name) const;

			virtual bool Data(std::string const &name, std::string *value) const;
			virtual bool Data(std::string const &name) const;

			virtual bool Parameter(std::string const &name, messages::task::Task::Parameter *parameter) const;

			bool Parameter(std::string const &name, double *value) const;
			bool Parameter(std::string const &name) const;

			virtual bool ReadRequest(std::istream &stream);

			operator bool() const;
			bool HasTask() const;

			void Save(std::string const &filename);
			void Save(std::ostream &stream);
		protected:
			void ReadRequest(messages::task::Task const &task);
		private:
			void ReadSettings();
			void ReadParameters();
			void ReadData();
	};
}

#endif /* __OPTIMIZATION_TASK_READER_H__ */
