#ifndef __OPTIMIZATION_FITNESS_H__
#define __OPTIMIZATION_FITNESS_H__

#include <base/Object/object.hh>
#include <base/Enum/enum.hh>
#include <optimization/Settings/settings.hh>
#include <cpg-network/cpg-network.h>

namespace optimization
{
	class Fitness : public base::Object
	{
		public:
			/* Public functions */
			Fitness();
			
			std::string const &name() const;
			void setName(std::string const &name);
			
			Settings const &settings() const;
			Settings &settings();

			virtual void reset();
			
			virtual bool operator<(Fitness const &other) const;
			virtual bool operator>(Fitness const &other) const;
			
			virtual void update(std::map<std::string, double> const &fitness);
			
			virtual Fitness *clone() const;
			virtual Fitness *copy() const;
			
			virtual std::map<std::string, double> const &components() const;
			
			virtual std::vector<double> values() const;
			virtual double value() const;
		private:
			struct Data : public base::Object::PrivateData
			{
				std::string name;
				std::map<std::string, double> components;

				Settings settings;
				
				CpgObject *state;
				CpgExpression *expression;
				
				Data();
				~Data();
			};
	
			Data *d_data;

			Fitness(std::vector<double> const &values, std::vector<double> const &weights);
			void compile();
			void compileCpg();
	};

	inline std::string const &Fitness::name() const
	{
		return d_data->name;
	}
	
	inline void Fitness::setName(std::string const &name)
	{
		d_data->name = name;
	}
	
	inline Settings const &Fitness::settings() const
	{
		return d_data->settings;
	}
	
	inline Settings &Fitness::settings()
	{
		return d_data->settings;
	}
	
	inline std::map<std::string, double> const &Fitness::components() const
	{
		return d_data->components;
	}
}

#endif /* __OPTIMIZATION_FITNESS_H__ */

