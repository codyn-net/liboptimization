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
