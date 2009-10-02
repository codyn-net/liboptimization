#ifndef __OPTIMIZATION_FITNESS_H__
#define __OPTIMIZATION_FITNESS_H__

#include <base/Object/object.hh>
#include <base/Enum/enum.hh>
#include <optimization/Settings/settings.hh>
#include <cpg-network/cpg-network.h>

#include <map>
#include <string>

namespace optimization
{
	class Fitness : public base::Object
	{
		public:
			typedef std::map<std::string, double> Values;

			/* Public functions */
			Fitness();
			
			Settings const &settings() const;
			Settings &settings();

			double evaluate(Values const &values);
			
			Fitness *clone() const;
			Fitness *copy() const;
		private:
			struct Data : public base::Object::PrivateData
			{
				Settings settings;
				
				CpgObject *state;
				CpgExpression *expression;
				
				double value;
				
				Data();
				~Data();
			};
	
			Data *d_data;

			void compile();
			void compileCpg();
	};
	
	inline Settings const &Fitness::settings() const
	{
		return d_data->settings;
	}
	
	inline Settings &Fitness::settings()
	{
		return d_data->settings;
	}
}

#endif /* __OPTIMIZATION_FITNESS_H__ */

