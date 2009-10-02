#ifndef __OPTIMIZATION_SOLUTION_H__
#define __OPTIMIZATION_SOLUTION_H__

#include <map>

#include <base/Object/object.hh>
#include <math/Random/random.hh>

#include <optimization/Fitness/fitness.hh>
#include <optimization/Parameters/parameters.hh>
#include <optimization/State/state.hh>

namespace optimization
{
	class Solution : public base::Object
	{
		public:
			/* Public functions */
			Solution();
			Solution(size_t id, Parameters const &parameters, State const &state);

			size_t id() const;
			
			Parameters &parameters();
			Parameters const &parameters() const;
			
			Fitness::Values &fitness();
			Fitness::Values const &fitness() const;			
			
			State &state();
			State const &state() const;
			
			std::string const &data() const;
			void setData(std::string const &data);

			virtual Solution *clone() const;
			virtual Solution *copy() const;
			
			// Manipulating individual parameters
			Parameters::value_type &addParameter(std::string const &name, Boundaries::value_type const &boundary);			
			virtual Parameters::value_type &addParameter(Parameters::value_type const &other);
			virtual int removeParameter(std::string const &name);
			
			virtual void reset();

			virtual operator std::string() const;
		protected:
			virtual void copy(Solution const &other);
		private:
			struct Data : public base::Object::PrivateData
			{
				/* Instance data */
				size_t id;

				Parameters parameters;
				Fitness::Values fitness;

				State state;
				
				std::string data;
			};
	
			Data *d_data;

			void initialize(size_t id, Parameters const &parameters, State const &state);
	};

	inline size_t Solution::id() const
	{
		return d_data->id;
	}

	inline Parameters &Solution::parameters()
	{
		return d_data->parameters;
	}

	inline Parameters const &Solution::parameters() const
	{
		return d_data->parameters;
	}

	inline Fitness::Values &Solution::fitness()
	{
		return d_data->fitness;
	}
	
	inline Fitness::Values const &Solution::fitness() const
	{
		return d_data->fitness;
	}
	
	inline State &Solution::state()
	{
		return d_data->state;
	}

	inline State const &Solution::state() const
	{
		return d_data->state;
	}
	
	inline std::string const &Solution::data() const
	{
		return d_data->data;
	}
	
	inline void Solution::setData(std::string const &data)
	{
		d_data->data = data;
	}
}

#endif /* __OPTIMIZATION_SOLUTION_H__ */

