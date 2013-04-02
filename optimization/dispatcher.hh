/*
 *  dispatcher.hh - This file is part of liboptimization
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

#ifndef __OPTIMIZATION_DISPATCHER_H__
#define __OPTIMIZATION_DISPATCHER_H__

#include <optimization/messages/task.pb.h>
#include <optimization/taskreader.hh>
#include <map>
#include <string>

namespace optimization
{
	/* Main dispatcher class.
	 *
	 * The dispatcher class is the main class that drives the dispatcher process.
	 * It is mostly a convenience class that does the boring work such as reading
	 * the dispatcher task request and writing a response message back to the
	 * worker process.
	 *
	 * Using this class is pretty straightforward. You first instantiate
	 * an object with input and output streams. The default constructor
	 * uses stdin and stdout which are used for when writing a dispatcher
	 * process. Constructing the dispatcher blocks until a task has been
	 * successfully received from the input stream. Task parameters and
	 * settings can be accessed using the <optimization::TaskReader>
	 * (base class) methods.
	 *
	 * When the dispatcher is finished evaluating the task, it can use the
	 * convenience methods <Respond> to directly write a response with
	 * a given fitness value to the output stream. The <AddFitness>,
	 * <SetFitness>, <AddData> and <SetData> methods can be used to
	 * accumulate fitness and data values which will be written when you
	 * call <WriteResponse>.
	 */
	class Dispatcher : public TaskReader
	{
		struct PrivateData;

		PrivateData *d;

		public:
			Dispatcher();
			Dispatcher(std::istream &stream, std::ostream &output);

			virtual ~Dispatcher();

			bool WriteResponse();

			void SetResponse(messages::task::Response const &response);

			void AddFitness(std::string const &name, double value);
			void SetFitness(std::map<std::string, double> const &fitness);

			void AddData(std::string const &name, std::string const &value);
			void SetData(std::map<std::string, std::string> const &data);

			void Respond(double fitness);
			void Respond(std::map<std::string, double> const &fitness);

			void Respond(double fitness, std::map<std::string, std::string> const &data);
			void Respond(std::map<std::string, double> const &fitness, std::map<std::string, std::string> const &data);
		protected:
			Dispatcher(bool lazyInit);
			void Initialize(std::istream &stream, std::ostream &output);
		private:
			void SetupResponse();
	};
}

#endif /* __OPTIMIZATION_DISPATCHER_H__ */
