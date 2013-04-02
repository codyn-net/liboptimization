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
	/* Convenience optimization class for webots.
	 *
	 * Webots is a convenient class for evaluating
	 * optimization solutions in webots. It is used in conjunction with the
	 * webots dispatcher. Internally, the webots dispatcher sets up a communication
	 * channel on which it sends the task request and listens for a response. This
	 * class makes it easy to read that request and to send a response back from
	 * your webots controller (or physics plugin).
	 *
	 * The class is a singleton from which you can get an instance using
	 * <Instance>. A basic use of the class is the following:
	 *
	 *     [code]
	 *     // Get optimization instance
	 *     optimization::Webots &optim = optimization::Webots::Instance();
	 *     
	 *     // See if we are in optimization mode
	 *     if (optim)
	 *     {
	 *         double x1, x2;
	 *     
	 *         optim.Parameter("x1", &x1);
	 *         optim.Parameter("x2", &x2);
	 *     }
	 *     
	 *     // Run webots loop
	 *     
	 *     if (optim)
	 *     {
	 *         // Send back fitness
	 *         double distance = calculateDistance();
	 *     
	 *         optim.Respond(distance);
	 *     }
	 *
	 * You can read additional settings as supplied in for instance a job xml file,
	 * using Setting(). For instance, if you want to have your simulation run a
	 * certain amount of time while measuring the performance of your robot, you
	 * could add a MaximumTime setting, and read it using <Setting>. Then after
	 * running the simulation for that amount of time, use <Respond> to send back
	 * the fitness of the simulation and quit the simulation.
	 *
	 * Use <Task> to get the <optimization::messages::task::Task>
	 * object to get the particular parameters and boundaries for the task that
	 * has to be executed.
	 *
	 * If you want to send additional data back to the optimizer, you can use
	 * one of the <Respond> functions that accepts an additional map of string key
	 * values. The optimizer will save this additional data so you can extract
	 * it later.
	 */
	class Webots : public Dispatcher
	{
		static Webots *s_instance;

		struct PrivateData;

		PrivateData *d;

		public:
			static Webots &Instance();
			virtual ~Webots();
		private:
			Webots();

			int Connect();
			void Disconnect(int s);

			void SetupPeriodicPing();
			void PeriodicPing();
			static void *PeriodicPingThread(void *ptr);
	};
}

#endif /* __OPTIMIZATION_WEBOTS_H__ */
