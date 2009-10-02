#ifndef __OPTIMIZATION_DISPATCHER_H__
#define __OPTIMIZATION_DISPATCHER_H__

#include <optimization/Messages/task.pb.h>
#include <glibmm.h>

namespace optimization
{
	class Dispatcher
	{
		messages::task::Task::Description d_request;
		Glib::RefPtr<Glib::MainLoop> d_main;

		public:
			/* Public functions */
			virtual bool run();
			
			messages::task::Task::Description &request();

			bool setting(std::string const &key, std::string &value) const;
			bool setting(std::string const &key) const;
		protected:
			virtual bool readRequest();
			virtual bool writeResponse(messages::task::Response &response);

			virtual bool runSolution() = 0;
			
			virtual bool useMainLoop() const;
			
			Glib::RefPtr<Glib::MainLoop> main();
		private:
			/* Private functions */
		
	};
	
	inline messages::task::Task::Description &Dispatcher::request()
	{
		return d_request;
	}
}

#endif /* __OPTIMIZATION_DISPATCHER_H__ */
