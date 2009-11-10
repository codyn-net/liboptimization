#ifndef __OPTIMIZATION_DEBUG_H__
#define __OPTIMIZATION_DEBUG_H__

#include <base/Debug/debug.hh>

#define debug_optimization_out(domain) (base::Debug::out(optimization::Debug::Domain::domain, #domain,  __FILE__, __FUNCTION__, __LINE__))

#define debug_worker (debug_optimization_out(Worker))
#define debug_master (debug_optimization_out(Master))

namespace optimization
{
	class Debug : public base::Debug
	{
		public:
			struct Domain
			{
				enum Values
				{
					Worker = base::Debug::Domain::User << 1,
					Master = base::Debug::Domain::User << 2,
					User = base::Debug::Domain::User << 5
				};
			};
	};
}

#endif /* __OPTIMIZATION_DEBUG_H__ */

