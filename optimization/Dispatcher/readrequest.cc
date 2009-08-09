#include "dispatcher.ih"

bool Dispatcher::readRequest() 
{
	/* Read request from stdin */
	size_t num;
	
	if (!(cin >> num))
	{
		cerr << "** [Dispatcher] Could not read message size" << endl;
		return false;
	}
	
	if (!cin.ignore(1, ' '))
	{
		cerr << "** [Dispatcher] Invalid message header" << endl;
		return false;
	}
	
	char *s = new char[num + 1];
	bool ret = false;
	
	if (cin.read(s, num))
	{		
		if (d_request.ParseFromArray(s, num))
			ret = true;
		else
			cerr << "** [Dispatcher] Could not parse message from array" << endl;
	}
	else
	{
		cerr << "** [Dispatcher] Could not read message" << endl;
	}
	
	delete[] s;
	return ret;
}
