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

/**
 * @class optimization::Messages
 * @brief Optimization messages
 *
 * Class providing useful functions to serialize and deserialize protobuf
 * messages. In particular, extract messages from data received from a
 * FileDescriptor (see Extract()) can be very convenient. Messages can
 * be serialized using Create().
 *
 */

/**
 * @brief Serialize protobuf message to string.
 * @param message message to serialize
 * @param serialized serialized return value
 *
 * Serializes a protobuf message to a string.
 *
 * @return true if serialization was successful, false otherwise
 * @fn bool Messages::Create(::google::protobuf::Message const &message, std::string &serialized)
 */
bool
Messages::Create(::google::protobuf::Message const &message,
                 string                            &serialized)
{
	if (!message.SerializeToString(&serialized))
	{
		return false;
	}
	
	stringstream s;
	
	size_t len = serialized.length();
	s << len << " " << serialized;
	
	serialized = s.str();
	return true;
}
