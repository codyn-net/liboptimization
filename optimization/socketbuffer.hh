#ifndef __OPTIMIZATION_SOCKET_BUFFER_H__
#define __OPTIMIZATION_SOCKET_BUFFER_H__

#include <iostream>

namespace optimization
{
	class SocketBuffer : public std::streambuf
	{
		struct PrivateData;

		PrivateData *d;
	public:
		SocketBuffer(int s);
		~SocketBuffer();

		int underflow();

		int overflow(int c);
		int sync();
		std::streamsize xputn(char const *s, std::streamsize n);
	};

	class SocketStream : private SocketBuffer, public std::iostream
	{
	public:
		SocketStream(int s)
		:
			SocketBuffer(s),
			std::iostream(this)
		{
		}
	};
}

#endif /* __OPTIMIZATION_SOCKET_BUFFER_H__ */

