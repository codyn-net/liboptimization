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

#include <network/network.hh>

namespace optimization
{
	class Discovery : public network::UdpServer
	{
		public:
			struct Info
			{
				std::string connection;
				std::string host;
			};
			
			/* Constructor/destructor */
			Discovery();
		
			void setNs(std::string const &ns);
			std::string const &ns() const;
			
			/* Public functions */
			base::signals::Signal<Info> &onGreeting();
			base::signals::Signal<Info> &onWakeup();
			
			virtual bool listen();
		private:
			/* Private functions */
			struct Data : public base::Object::PrivateData
			{
				std::string ns;
				
				base::signals::Signal<Info> onGreeting;
				base::signals::Signal<Info> onWakeup;

				bool onDataHandler(UdpServer::DataArgs &args);
				bool checkNs(std::string const &ns) const;
			};
			
			Data *d_data;
	};
	
	inline base::signals::Signal<Discovery::Info> &Discovery::onGreeting()
	{
		return d_data->onGreeting;
	}
	
	inline base::signals::Signal<Discovery::Info> &Discovery::onWakeup()
	{
		return d_data->onWakeup;
	}
}

#endif /* __OPTIMIZATION_DISCOVERY_H__ */
