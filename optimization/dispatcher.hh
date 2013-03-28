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

namespace optimization
{
	class Dispatcher : public TaskReader
	{
		struct PrivateData;

		PrivateData *d;

		public:
			Dispatcher();
			Dispatcher(std::istream &stream, std::ostream &out);
			virtual ~Dispatcher();

			virtual bool WriteResponse();

			virtual void SetResponse(messages::task::Response const &response);

			virtual void AddFitness(std::string const &name, double value);
			virtual void SetFitness(std::map<std::string, double> const &fitness);

			virtual void AddData(std::string const &name, std::string const &value);
			virtual void SetData(std::map<std::string, std::string> const &data);

			virtual bool ReadRequest(std::istream &stream);
		protected:
			virtual bool WriteResponse(std::string const &s);
		private:
			void SetupResponse();
	};
}

#endif /* __OPTIMIZATION_DISPATCHER_H__ */
