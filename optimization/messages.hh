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

#include <vector>
#include <string>
#include <sstream>
#include <google/protobuf/message.h>
#include <optimization/messages/task.pb.h>
#include <optimization/messages/discovery.pb.h>
#include <optimization/messages/command.pb.h>
#include <optimization/messages/monitor.pb.h>

namespace optimization
{
	/* Convenience methods for extracting and creating messages.
	 *
	 * Messages is a class providing two convenience methods for extracting
	 * a protobuf message from an input stream (<Extract>) and for creating
	 * a serialized message from a protobuf message (<Create>).
	 */
	class Messages
	{
	public:
		template <typename T>
		static bool Extract(std::istream &stream, T &message);

		static bool Create(::google::protobuf::Message const &message,
		                   std::string                       *serialized);

		static bool Write(::google::protobuf::Message const &message,
		                  std::ostream                      &stream);
	};

	/* Extract protobuf messages from streams.
	 * @stream the input stream.
	 * @message return value for receive message.
	 *
	 * Extract a protobuf message of type <T> from the input <stream>.
	 *
	 * @return true if a message was successfully extracted, false otherwise.
	 */
	template <typename T>
	bool Messages::Extract(std::istream &stream, T &message)
	{
		size_t num;

		if (!(stream >> num))
		{
			return false;
		}

		if (!stream.ignore(1, ' '))
		{
			return false;
		}

		char *buffer = new char[num + 1];
		bool ret = true;

		if (!stream.read(buffer, num))
		{
			ret = false;
		}
		else
		{
			buffer[num] = '\0';

			try
			{
				message.ParseFromArray(buffer, num);
			}
			catch (std::exception e)
			{
				ret = false;
			}
		}

		delete[] buffer;
		return ret;
	}
}

#endif /* __OPTIMIZATION_MESSAGES_H__ */
