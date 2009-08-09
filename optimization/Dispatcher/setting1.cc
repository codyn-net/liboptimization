#include "dispatcher.ih"

bool Dispatcher::setting(string const &key, string &value) const
{
	size_t num = d_request.settings_size();
	
	for (size_t i = 0; i < num; ++i)
	{
		messages::worker::Request::Dispatch::KeyValue const &kv = d_request.settings(i);

		if (kv.key() == key)
		{
			value = kv.value();
			return true;
		}
	}
	
	return false;
}
