#include "webots.ih"

bool Webots::setting(string const &key) const
{
	string dummy;
	return setting(key, dummy);
}
