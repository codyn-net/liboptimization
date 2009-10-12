#include "dispatcher.ih"

void Dispatcher::readSettings()
{
	size_t num = d_request.settings_size();
	
	for (size_t i = 0; i < num; ++i)
	{
		messages::task::Task::Description::KeyValue const &kv = d_request.settings(i);
		d_settings[kv.key()] = kv.value();
	}
}
