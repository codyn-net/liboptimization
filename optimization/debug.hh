#ifndef __OPTIMIZATION_DEBUG_H__
#define __OPTIMIZATION_DEBUG_H__

#include <jessevdk/base/base.hh>

#define debug_optimization_out(domain) (jessevdk::base::Debug::Out(optimization::Debug::Domain::domain, #domain,  __FILE__, __FUNCTION__, __LINE__))

#define debug_worker (debug_optimization_out(Worker))
#define debug_master (debug_optimization_out(Master))

namespace optimization
{
	/** @brief Optimization debug class.
	 *
	 * Simple debug class for debugging optimization framework.
	 **/
	class Debug : public jessevdk::base::Debug
	{
		public:
			/** @brief Optimization debug domains.
			 **/
			struct Domain
			{
				enum Values
				{
					Worker = jessevdk::base::Debug::Domain::Last << 1,
					Master = jessevdk::base::Debug::Domain::Last << 2,
					Last = jessevdk::base::Debug::Domain::Last << 5
				};
			};
	};
}

#endif /* __OPTIMIZATION_DEBUG_H__ */

