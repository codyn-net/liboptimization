/*
 *  webots.hh - This file is part of liboptimization
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

#ifndef __OPTIMIZATION_WEBOTS_H__
#define __OPTIMIZATION_WEBOTS_H__

#include <optimization/messages/task.pb.h>
#include <jessevdk/network/network.hh>
#include <jessevdk/os/os.hh>
#include <optimization/taskreader.hh>

#include <map>
#include <string>

namespace optimization
{
	class Webots : public TaskReader
	{
		static Webots *s_instance;

		jessevdk::network::Client d_client;

		public:
			/* Constructor/destructor */
			static Webots &Instance();

			/* Public functions */
			void Response(messages::task::Response &response);

			void Respond(double fitness);
			void Respond(std::map<std::string, double> const &fitness);
			void Respond(messages::task::Response::Status status, std::map<std::string, double> const &fitness);

			void Respond(double fitness, std::map<std::string, std::string> const &data);
			void Respond(std::map<std::string, double> const &fitness, std::map<std::string, std::string> const &data);
			void Respond(messages::task::Response::Status status, std::map<std::string, double> const &fitness, std::map<std::string, std::string> const &data);

			void RespondFail();

			operator bool() const;
			void WaitForRequest();
		private:
			/* Private functions */
			Webots();
			void OnData(jessevdk::os::FileDescriptor::DataArgs &args);

			void PeriodicPing();
	};
}

#endif /* __OPTIMIZATION_WEBOTS_H__ */
