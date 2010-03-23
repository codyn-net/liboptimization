/*
 *  discovery.hh - This file is part of liboptimization
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

#ifndef __OPTIMIZATION_DISCOVERY_H__
#define __OPTIMIZATION_DISCOVERY_H__

#include <jessevdk/network/network.hh>

namespace optimization
{
	class Discovery : public jessevdk::network::UdpServer
	{
		public:
			struct Info
			{
				/** Advertized connection string */
				std::string Connection;
				
				/** Host name of client connection */
				std::string Host;
			};
			
			/* Constructor/destructor */
			Discovery();
		
			void SetNamespace(std::string const &ns);
			std::string const &Namespace() const;
			
			/* Public functions */
			jessevdk::base::signals::Signal<Info> &OnGreeting();
			jessevdk::base::signals::Signal<Info> &OnWakeup();
			
			virtual bool Listen();
		private:
			/* Private functions */
			struct Data : public jessevdk::base::Object::PrivateData
			{
				std::string ns;
				
				jessevdk::base::signals::Signal<Info> onGreeting;
				jessevdk::base::signals::Signal<Info> onWakeup;

				void OnDataHandler(UdpServer::DataArgs &args);
				bool CheckNamespace(std::string const &ns) const;
			};
			
			Data *d_data;
	};
}

#endif /* __OPTIMIZATION_DISCOVERY_H__ */
