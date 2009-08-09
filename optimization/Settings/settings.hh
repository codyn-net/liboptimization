#ifndef __OPTIMIZATION_SETTINGS_H__
#define __OPTIMIZATION_SETTINGS_H__

#include <base/Object/object.hh>
#include <base/Properties/properties.hh>

#include <list>

namespace optimization
{
	class Settings : public base::Object, public base::Properties
	{
		struct Data : public base::Object::PrivateData
		{
			std::list<std::string> storage;
		};
		
		Data *d_data;

		public:
			/* Public functions */
			Settings();
			
			bool hasProperty(std::string const &name);
			bool propertyExists(std::string const &name);
		protected:
			virtual base::PropertyBase &getProperty(std::string const &name);
		private:
			base::PropertyBase &storeProperty(std::string const &name);
	};
}

#endif /* __OPTIMIZATION_SETTINGS_H__ */

