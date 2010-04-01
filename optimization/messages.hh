/*
 *  messages.hh - This file is part of liboptimization
 *
 *  Copyright (C) 2009 - Jesse van den Kieboom
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as published by the
 * Free Software Foundation; either version 2.1 of the License, or (at your
 * option) any later version.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License
 * for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this library; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#ifndef __OPTIMIZATION_MESSAGES_H__
#define __OPTIMIZATION_MESSAGES_H__

#include <jessevdk/os/os.hh>
#include <vector>
#include <string>
#include <sstream>
#include <google/protobuf/message.h>
#include <optimization/task.pb.h>
#include <optimization/discovery.pb.h>
#include <optimization/command.pb.h>

namespace optimization
{
	class Messages
	{
		public:
			template <typename T>
			static void Extract(jessevdk::os::FileDescriptor::DataArgs &args, std::vector<T> &messages);

			static bool Create(::google::protobuf::Message const &message, std::string &serialized);
	};

	/**
 * @brief Extract protobuf messages from buffered data.
	 * @param args the data args from a file descriptor (socket, stream, file)
	 * @param messages return value for received messages
	 *
	 * Extract protobuf messages from data as received from a FileDescriptor or
	 * any subclass of FileDescriptor.
	 *
	 */
	template <typename T>
	void Messages::Extract(jessevdk::os::FileDescriptor::DataArgs &args, std::vector<T> &messages)
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

			if (!s.ignore(1, ' '))
			{
				break;
			}

			char *buffer = new char[num + 1];

			if (!s.read(buffer, num))
			{
				delete[] buffer;
				break;
			}

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

		args.Buffer(data);
	}
}

#endif /* __OPTIMIZATION_MESSAGES_H__ */
