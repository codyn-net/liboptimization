#ifndef __OPTIMIZATION_BOUNDARIES_H__
#define __OPTIMIZATION_BOUNDARIES_H__

#include <base/Object/object.hh>
#include <optimization/Container/container.hh>
#include <string>
#include <map>

namespace optimization
{
	namespace container
	{
		struct Boundary
		{
			std::string name;
			double min;
			double max;
		};
	};
	
	class Boundaries : public Container<container::Boundary>
	{
		public:
			Boundaries();
			Boundaries(const_iterator begin, const_iterator end);

			container::Boundary &add(container::Boundary const &item);
			container::Boundary &add(std::string const &name, double min, double max);
			
			virtual Boundaries *clone() const;
			virtual Boundaries *copy() const;
		private:
	};	
}

#endif /* __OPTIMIZATION_BOUNDARIES_H__ */

