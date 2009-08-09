#include "webots.ih"

void Webots::waitForRequest() const
{
	Glib::RefPtr<Glib::MainContext> ctx = Glib::MainContext::get_default();

	while (!hasRequest())
	{
		ctx->iteration(true);
	}
}
