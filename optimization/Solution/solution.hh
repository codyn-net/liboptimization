#ifndef __OPTIMIZATION_SOLUTION_H__
#define __OPTIMIZATION_SOLUTION_H__

#include <map>

#include <base/Object/object.hh>
#include <math/Random/random.hh>

#include <optimization/Fitness/fitness.hh>
#include <optimization/Parameters/parameters.hh>
#include <optimization/Settings/settings.hh>

namespace optimization
{
	class Solution : public base::Object
	{
		public:
			class ExtensionData
			{
				public:
					virtual ExtensionData *copy() const = 0;
					virtual ~ExtensionData() {};
			};

			/* Public functions */
			Solution();
			Solution(size_t id, Parameters const &parameters, Fitness const &fitness, math::Random const &random, Settings const &settings);

			Fitness &fitness();
			Parameters &parameters();
			
			size_t id() const;
			
			Fitness const &fitness() const;
			Parameters const &parameters() const;
			
			math::Random &random();
			math::Random const &random() const;
			
			Settings &settings();
			Settings const &settings() const;

			virtual Solution *clone() const;
			virtual Solution *copy() const;
			
			Parameters::value_type &addParameter(std::string const &name, Boundaries::value_type const &boundary);			
			virtual Parameters::value_type &addParameter(Parameters::value_type const &other);
			virtual int removeParameter(std::string const &name);
			
			virtual void reset();
			virtual operator std::string() const;

			void addData(std::string const &name, ExtensionData *data);
			
			template <typename T>
			T &getData(std::string const &name);
			
			template <typename T>
			T const &getData(std::string const &name) const;
			
			virtual void clear();
		protected:
			void setFitness(Fitness const &fitness);
			virtual void copy(Solution const &other);
		private:
			struct Data : public base::Object::PrivateData
			{
				/* Instance data */
				size_t id;
				base::Cloneable<Fitness> fitness;
				base::Cloneable<Parameters> parameters;
				
				std::map<std::string, ExtensionData *> extensionData;

				math::Random random;
				Settings settings;

				~Data();
				
				void clear();
			};
	
			Data *d_data;

			void initialize(size_t id, Parameters const &parameters, Fitness const &fitness, math::Random const &random, Settings const &settings);
	};

	inline Fitness &Solution::fitness()
	{
		return d_data->fitness;
	}
	
	inline Parameters &Solution::parameters()
	{
		return d_data->parameters;
	}
	
	inline Fitness const &Solution::fitness() const
	{
		return d_data->fitness;
	}
	
	inline math::Random &Solution::random()
	{
		return d_data->random;
	}
	
	inline math::Random const &Solution::random() const
	{
		return d_data->random;
	}
	
	inline size_t Solution::id() const
	{
		return d_data->id;
	}
	
	inline Parameters const &Solution::parameters() const
	{
		return d_data->parameters;
	}
	
	inline Settings const &Solution::settings() const
	{
		return d_data->settings;
	}
	
	inline Settings &Solution::settings()
	{
		return d_data->settings;
	}
	
	template <typename T>
	T &Solution::getData(std::string const &name)
	{
		return dynamic_cast<T &>(*d_data->extensionData[name]);
	}
	
	template <typename T>
	T const &Solution::getData(std::string const &name) const
	{
		return dynamic_cast<T const &>(*d_data->extensionData[name]);
	}
}

#endif /* __OPTIMIZATION_SOLUTION_H__ */

