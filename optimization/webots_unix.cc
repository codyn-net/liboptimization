#include "webots.hh"

#include "webots_unix.hh"

using namespace std;
using namespace optimization;

int
Webots::Connect()
{
	char *sockname;
	int s;

	sockname = getenv("OPTIMIZATION_UNIX_SOCKET");

	if (!sockname || !*sockname)
	{
		return -1;
	}

	s = socket(PF_UNIX, SOCK_STREAM, 0);

	if (s < 0)
	{
		return -1;
	}

	struct sockaddr_un address;
	memset(&address, 0, sizeof(struct sockaddr_un));

	address.sun_family = AF_UNIX;
	snprintf(address.sun_path, sizeof(((sockaddr_un *)0)->sun_path), "%s", sockname);

	if (connect(s, (struct sockaddr *)&address, sizeof(struct sockaddr_un)) != 0)
	{
		close(s);
		return -1;
	}

	return s;
}

void
Webots::Disconnect(int s)
{
	if (s != -1)
	{
		shutdown(s, SHUT_RDWR);
		close(s);
	}
}

ssize_t
Webots::Receive(int s, void *sbuffer, size_t length, int flags)
{
	if (s == -1)
	{
		return -1;
	}

	return ::recv(s, sbuffer, length, flags);
}

ssize_t
Webots::Send(int s, void *sbuffer, size_t length, int flags)
{
	if (s == -1)
	{
		return -1;
	}

	return ::send(s, sbuffer, length, flags);
}

void
Webots::SetupPeriodicPing()
{
	pthread_t thread;
	pthread_create(&thread, NULL, Webots::PeriodicPingThread, (void *)this);
}
