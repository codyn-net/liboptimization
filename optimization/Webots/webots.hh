#ifndef __OPTIMIZATION_WEBOTS_H__
#define __OPTIMIZATION_WEBOTS_H__

#include <optimization/Messages/worker.pb.h>
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
		messages::worker::Request::Dispatch d_request;

		bool d_hasRequest;

		public:
			/* Constructor/destructor */
			static Webots &instance();

			/* Public functions */
			messages::worker::Request::Dispatch &request();
			void response(messages::worker::Response &response);
			
			void respond(std::map<std::string, double> const &fitness);
			void respond(messages::worker::Response::Status status, std::map<std::string, double> const &fitness);

			void respondFail();
			
			operator bool() const;
			bool hasRequest() const;
			
			void waitForRequest() const;
			
			bool setting(std::string const &key, std::string &value) const;
			bool setting(std::string const &key) const;
		private:
			/* Private functions */
			Webots();
			
			bool onData(os::FileDescriptor::DataArgs &args);
	};
}

#endif /* __OPTIMIZATION_WEBOTS_H__ */
