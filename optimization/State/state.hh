#ifndef __OPTIMIZATION_STATE_H__
#define __OPTIMIZATION_STATE_H__

#include <math/math.hh>
#include <optimization/Settings/settings.hh>

namespace optimization
{
	struct State
	{
		Settings settings;
		math::Random random;
	};
}

#endif /* __OPTIMIZATION_STATE_H__ */
