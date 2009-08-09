#ifndef __OPTIMIZATION_PARAMETERS_H__
#define __OPTIMIZATION_PARAMETERS_H__

#include <optimization/Container/container.hh>
#include <optimization/Boundaries/boundaries.hh>

namespace optimization
{
	namespace container
	{
		struct Parameter
		{
			std::string name;
			Boundaries::value_type boundary;
			double value;
		};
	};
	
	class Parameters : public Container<container::Parameter>
	{
		public:
			Parameters();
			Parameters(const_iterator begin, const_iterator end);
			
			container::Parameter &add(container::Parameter const &item);
			container::Parameter &add(std::string const &name);
			container::Parameter &add(std::string const &name, Boundaries::value_type const &boundary);
			
			virtual Parameters *clone() const;
			virtual Parameters *copy() const;
			
			operator std::vector<double>() const;
			std::vector<double> values() const;
		private:
			/* Private functions */
		
	};
}

#endif /* __OPTIMIZATION_PARAMETERS_H__ */
