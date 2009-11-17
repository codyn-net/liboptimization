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

#include <optimization/task.pb.h>
#include <network/network.hh>
#include <os/os.hh>
#include <map>
#include <string>

namespace optimization
{
	class Webots
	{
		static Webots *s_instance;

		network::Client d_client;
		messages::task::Task::Description d_request;
		std::map<std::string, std::string> d_settings;
		std::map<std::string, messages::task::Task::Description::Parameter> d_parameters;

		bool d_hasRequest;

		public:
			/* Constructor/destructor */
			static Webots &Instance();

			/* Public functions */
			messages::task::Task::Description &Request();
			void Response(messages::task::Response &response);
			
			void Respond(double fitness);
			void Respond(std::map<std::string, double> const &fitness);
			void Respond(messages::task::Response::Status status, std::map<std::string, double> const &fitness);

			void Respond(double fitness, std::map<std::string, std::string> const &data);
			void Respond(std::map<std::string, double> const &fitness, std::map<std::string, std::string> const &data);
			void Respond(messages::task::Response::Status status, std::map<std::string, double> const &fitness, std::map<std::string, std::string> const &data);

			void RespondFail();
			
			operator bool() const;
			bool HasRequest() const;
			
			void WaitForRequest();
			
			bool Setting(std::string const &key, std::string &value);
			bool Setting(std::string const &key);
			
			bool Parameter(std::string const &name, messages::task::Task::Description::Parameter &parameter);
			bool Parameter(std::string const &name);
		private:
			/* Private functions */
			Webots();

			void ReadSettings();
			void ReadParameters();
			
			void OnData(os::FileDescriptor::DataArgs &args);
	};
}

#endif /* __OPTIMIZATION_WEBOTS_H__ */
