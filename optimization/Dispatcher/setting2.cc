#include "dispatcher.ih"

bool Dispatcher::setting(string const &key) const
{
	string dummy;
	return setting(key, dummy);
}
