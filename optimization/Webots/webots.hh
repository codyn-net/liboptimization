#ifndef __OPTIMIZATION_WEBOTS_H__
#define __OPTIMIZATION_WEBOTS_H__

#include <optimization/Messages/task.pb.h>
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

		bool d_hasRequest;

		public:
			/* Constructor/destructor */
			static Webots &instance();

			/* Public functions */
			messages::task::Task::Description &request();
			void response(messages::task::Response &response);
			
			void respond(std::map<std::string, double> const &fitness);
			void respond(messages::task::Response::Status status, std::map<std::string, double> const &fitness);

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
