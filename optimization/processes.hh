#ifndef __OPTIMIZATION_PROCESSES_H__
#define __OPTIMIZATION_PROCESSES_H__

#include <vector>
#include <sys/types.h>
#include <map>

namespace optimization
{
	class Processes
	{
		public:
			static pid_t Parent(pid_t pid);
			static std::vector<pid_t> Children(pid_t pid, bool recurse = false);
		private:
			static std::vector<pid_t> Collect(std::map<pid_t, std::vector<pid_t> > const &mapping, pid_t parent, bool recurse);
	};
}

#endif /* __OPTIMIZATION_PROCESSES_H__ */

