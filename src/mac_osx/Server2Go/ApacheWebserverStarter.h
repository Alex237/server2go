/*
 *  ApacheWebserverStarter.h
 *  Server2Go
 *
 *  Created by Timo Haberkern on 12.07.07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#include <wx/string.h>
#include <wx/process.h>
 
class ApacheWebserverStarter
{
	public:
		ApacheWebserverStarter();
		long StartUp(wxString serverpath, wxString temppath);
};
