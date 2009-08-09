#ifndef __OPTIMIZATION_CONSTANTS_H__
#define __OPTIMIZATION_CONSTANTS_H__

#include <string>

namespace optimization
{
	struct Constants
	{
		enum
		{
			DiscoveryPort = 4756,
			WorkerPort = 8723,
			CommandPort = 7592
		};
		
		static std::string DiscoveryGroup;
	};
}

#endif /* __OPTIMIZATION_CONSTANTS_H__ */

