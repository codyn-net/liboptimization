/*
 *  run.cc - This file is part of liboptimization
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

#include "dispatcher.ih"

bool Dispatcher::run() 
{
	Glib::init();
	
	if (!readRequest())
	{
		cerr << "** [Dispatcher] Invalid dispatch request" << endl;
		return false;
	}
	
	if (useMainLoop())
		d_main = Glib::MainLoop::create();
	
	if (!runSolution())
		return false;
	
	if (d_main)
		d_main->run();

	return true;
}
