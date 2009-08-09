#include "dispatcher.ih"

bool Dispatcher::run() 
{
	Glib::init();
	
	if (!readRequest())
	{
		cerr << "** [Dispatcher] Invalid dispatch request" << endl;
		return false;
	}
	
	if (useMainLoop())
		d_main = Glib::MainLoop::create();
	
	if (!runSolution())
		return false;
	
	if (d_main)
		d_main->run();

	return true;
}
