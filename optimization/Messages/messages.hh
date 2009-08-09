#ifndef __OPTIMIZATION_MESSAGES_H__
#define __OPTIMIZATION_MESSAGES_H__

#include <os/FileDescriptor/filedescriptor.hh>
#include <vector>
#include <string>
#include <sstream>
#include <google/protobuf/message.h>
#include <optimization/Messages/command.pb.h>
#include <optimization/Messages/worker.pb.h>
#include <optimization/Messages/discovery.pb.h>

namespace optimization
{
	class Messages
	{
		public:
			template <typename T>
			static void extract(os::FileDescriptor::DataArgs &args, std::vector<T> &messages);
			
			static bool create(::google::protobuf::Message const &message, std::string &serialized);
	};
	
	template <typename T>
	void Messages::extract(os::FileDescriptor::DataArgs &args, std::vector<T> &messages)
	{
		std::string data = args.data;
	
		while (true)
		{
			size_t num;
			std::stringstream s(data);

			if (!(s >> num))
			{
				break;
			}
	
			T message;
			char *buffer = new char[num + 1];

			if (!s.ignore(1, ' '))
				break;

			if (!s.read(buffer, num))
				break;

			buffer[num] = '\0';
			
			try
			{
				message.ParseFromArray(buffer, num);
			}
			catch (std::exception e)
			{
				std::cerr << "Problem with creating message: " << e.what() << std::endl;
				delete[] buffer;
				break;
			}

			delete[] buffer;

			data = data.substr(s.tellg());
			messages.push_back(message);
		}

		args.buffer(data);
	}
}

#endif /* __OPTIMIZATION_MESSAGES_H__ */
