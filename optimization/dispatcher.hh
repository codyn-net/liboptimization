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

#include <optimization/task.pb.h>
#include <glibmm.h>

namespace optimization
{
	class Dispatcher
	{
		messages::task::Task::Description d_request;
		std::map<std::string, std::string> d_settings;
		Glib::RefPtr<Glib::MainLoop> d_main;

		public:
			/* Public functions */
			virtual bool Run();
			
			messages::task::Task::Description &Request();

			bool Setting(std::string const &key, std::string &value) const;
			bool Setting(std::string const &key) const;
		protected:
			virtual bool ReadRequest();
			void ReadSettings();

			virtual bool WriteResponse(messages::task::Response &response);
			virtual bool RunTask() = 0;
			virtual bool UseMainLoop() const;
			
			Glib::RefPtr<Glib::MainLoop> Main();
		private:
			/* Private functions */
		
	};
}

#endif /* __OPTIMIZATION_DISPATCHER_H__ */