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
#include <optimization/dispatcher.hh>

#include <map>
#include <string>

namespace optimization
{
	class Webots : public Dispatcher
	{
		static Webots *s_instance;

		struct PrivateData;

		PrivateData *d;

		public:
			/* Constructor/destructor */
			static Webots &Instance();

			virtual ~Webots();

			/* Public functions */
			void Respond(double fitness);
			void Respond(std::map<std::string, double> const &fitness);

			void Respond(double fitness, std::map<std::string, std::string> const &data);
			void Respond(std::map<std::string, double> const &fitness, std::map<std::string, std::string> const &data);
		protected:
			virtual bool WriteResponse(std::string const &s);
		private:
			/* Private functions */
			Webots();

			int Connect();
			void Disconnect(int s);
			ssize_t Receive(int s, void *sbuffer, size_t length, int flags);
			ssize_t Send(int s, void *sbuffer, size_t length, int flags);

			void SetupPeriodicPing();
			void PeriodicPing();
			static void *PeriodicPingThread(void *ptr);
	};
}

#endif /* __OPTIMIZATION_WEBOTS_H__ */
