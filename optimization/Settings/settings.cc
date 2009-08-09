#include "settings.ih"

Settings::Settings()
:
	Object(),
	Properties(dynamic_cast<Object &>(*this))
{
	d_data = new Data();
	addPrivateData(d_data);
}
