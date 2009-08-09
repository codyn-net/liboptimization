#include "webots.ih"

Webots::operator bool() const
{
	return d_client;
}
