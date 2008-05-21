/*
 *  PortHelper.h
 *  Server2Go
 *
 *  Created by Timo Haberkern on 12.07.07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */
#include "wx/string.h"
 
class PortHelper
{
	public:
		static long getFreeWebserverPort(wxString hostname, long configValue);
		static long getFreeMySqlPort(wxString hostname, long configValue);
		static bool checkPort(wxString hostname, long port);
};