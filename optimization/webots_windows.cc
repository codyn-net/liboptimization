#include "webots.hh"

#include "webots_windows.hh"

using namespace std;
using namespace optimization;

int
Webots::Connect()
{
	char *sockport;

	sockport = getenv("OPTIMIZATION_TCP_PORT");

	if (!sockport || !*sockport)
	{
		return -1;
	}

	WSADATA wsaData;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		return -1;
	}

	struct addrinfo hints;
	struct addrinfo *addresses;

	memset(&hints, 0, sizeof(hints));

	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	if (::getaddrinfo("localhost", sockport, &hints, &addresses) != 0)
	{
		WSACleanup();
		return -1;
	}

	for (struct addrinfo *ptr = addresses; ptr; ptr = ptr->ai_next)
	{
		int s = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

		if (s < 0)
		{
			continue;
		}

		if (connect(s, ptr->ai_addr, (int)ptr->ai_addrlen) != 0)
		{
			closesocket(s);
			continue;
		}

		freeaddrinfo(addresses);
		return s;
	}

	freeaddrinfo(addresses);
	WSACleanup();

	return -1;
}

void
Webots::Disconnect(int s)
{
	if (s != -1)
	{
		closesocket(s);
		WSACleanup();
	}
}

typedef WINAPI unsigned (*WinThreadFunc)(void *);

void
Webots::SetupPeriodicPing()
{
	_beginthreadex(0, 0, (WinThreadFunc)&Webots::PeriodicPingThread, (void *)this, 0, 0);
}
