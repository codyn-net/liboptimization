#include "socketbuffer.hh"
#include <cstdio>
#include <cstdlib>

#ifdef MINGW
#include <winsock2.h>
#else
#include <sys/types.h>
#include <sys/socket.h>
#endif

using namespace optimization;
using namespace std;

struct SocketBuffer::PrivateData
{
	int socket;

	char *buffer;

	size_t contentsSize;
	size_t bufferSize;
};

SocketBuffer::SocketBuffer(int s)
{
	d = new PrivateData();

	d->socket = s;
	d->bufferSize = 1024 * 1024;
	d->contentsSize = 0;

	d->buffer = (char *)malloc(d->bufferSize);

	setg(d->buffer, d->buffer, d->buffer + d->contentsSize);
}

SocketBuffer::~SocketBuffer()
{
	if (d->buffer)
	{
		free(d->buffer);
	}

	delete d;
}

int
SocketBuffer::underflow()
{
	if (d->socket == -1)
	{
		return EOF;
	}

	if (d->bufferSize == d->contentsSize)
	{
		d->bufferSize *= 2;

		// Make buffer larger
		d->buffer = (char *)realloc(d->buffer, d->bufferSize);
	}

	ssize_t n = ::recv(d->socket, d->buffer + d->contentsSize, d->bufferSize - d->contentsSize, 0);

	if (n <= 0)
	{
		return EOF;
	}

	size_t newcontents = d->contentsSize + n;
	int ret = (int)*(d->buffer + d->contentsSize);

	setg(d->buffer, d->buffer + d->contentsSize, d->buffer + newcontents);
	d->contentsSize = newcontents;

	return ret;
}

int
SocketBuffer::overflow(int c)
{
	if (d->socket == -1)
	{
		return EOF;
	}

	streamsize n = pptr() - pbase();

	if (n > 0 && sync() != 0)
	{
		return EOF;
	}

	if (c != EOF)
	{
		char cbuf[1] = {
			static_cast<char>(c)
		};

		if (::send(d->socket, cbuf, sizeof(cbuf), 0) != sizeof(cbuf))
		{
			return EOF;
		}
	}

	pbump(-n);
	return 0;
}

streamsize
SocketBuffer::xputn(char const *s, std::streamsize n)
{
	if (d->socket == -1)
	{
		return -1;
	}

	if (sync() == EOF)
	{
		return 0;
	}

	return ::send(d->socket, s, n, 0);
}

int
SocketBuffer::sync()
{
	if (d->socket == -1)
	{
		return EOF;
	}

	streamsize n = pptr() - pbase();

	if (n > 0)
	{
		if (::send(d->socket, pbase(), n, 0) != n)
		{
			return EOF;
		}
		else
		{
			return 0;
		}
	}
	else
	{
		return 0;
	}
}
