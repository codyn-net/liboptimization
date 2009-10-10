/*
 *  ondata.cc - This file is part of liboptimization
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

#include "webots.ih"

bool Webots::onData(os::FileDescriptor::DataArgs &args) 
{
	vector<messages::task::Task::Description> request;
	vector<messages::task::Task::Description>::iterator iter;
	
	Messages::extract(args, request);
	
	for (iter = request.begin(); iter != request.end(); ++iter)
	{
		d_request = *iter;
		d_hasRequest = true;
		break;
	}
}
