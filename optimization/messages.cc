/*
 *  messages.cc - This file is part of liboptimization
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

#include "messages.hh"

using namespace std;
using namespace optimization;

/* Serialize protobuf message to string.
 * @message message to serialize.
 * @serialized serialized return value.
 *
 * Serialize serializes a protobuf message to a string. The serialization
 * first byte encodes the protobuf message. Then it prefixes the byte encoded
 * message with the length of the message (in ascii) and a space.
 *
 * @return true if serialization was successful, false otherwise
 */
bool
Messages::Create(::google::protobuf::Message const &message,
                 std::string                       *serialized)
{
	if (!serialized)
	{
		return true;
	}

	if (!message.SerializeToString(serialized))
	{
		return false;
	}

	stringstream s;

	size_t len = serialized->length();
	s << len << " " << *serialized;

	*serialized = s.str();
	return true;
}

/* WRite protobuf message to stream.
 * @message message to write.
 * @stream stream to write to.
 *
 * Write serializes a protobuf message and writes it to the given <stream>.
 * The serialization is done using <Create> which prefixes the byte encoded
 * message with the length of the message (in ascii) and a space.
 *
 * @return true if the write was successful, false otherwise
 */
bool
Messages::Write(::google::protobuf::Message const &message,
                std::ostream                      &stream)
{
	string serialized;

	if (!Create(message, &serialized))
	{
		return false;
	}

	stream.write(serialized.c_str(), serialized.length());
	stream.flush();

	return stream;
}
