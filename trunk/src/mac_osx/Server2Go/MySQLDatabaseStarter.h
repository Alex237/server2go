/*
 *  MySQLDatabaseStarter.h
 *  Server2Go
 *
 *  Created by Timo Haberkern on 12.07.07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */
 
#include <wx/string.h>
#include <wx/process.h>

#include "configuration.h"

class MySQLDatabaseStarter
{
	public:
		long StartUp(wxString serverpath, wxString temppath, long dwMySQLPort, Configuration *pConfig);
};