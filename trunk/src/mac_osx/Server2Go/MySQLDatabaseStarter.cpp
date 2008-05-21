/*
 *  MySQLDatabaseStarter.cpp
 *  Server2Go
 *
 *  Created by Timo Haberkern on 12.07.07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */
#include <wx/wx.h>
#include "MySQLDatabaseStarter.h"

long MySQLDatabaseStarter::StartUp(wxString serverpath, wxString temppath, long dwMySQLPort, Configuration *pConfig)
{
	wxString startpath = serverpath+ wxT("mysql/libexec/mysqld --defaults-file=") + temppath + wxT("my.ini");	
	startpath += _T(" --port=");
	
	wxString strport;
	strport << dwMySQLPort;
	
	startpath += strport;
	
	//--language
	
	//additionalParameters
	startpath += wxT(" ") + pConfig->m_strMySqlParameter;
	
	wxProcess *process_info;
	
	//wxMessageBox(startpath);
	
	process_info =  wxProcess::Open(startpath);
	//--- wxMAC seems not to implement the GetPid method!?!!?? So return 0 to the caller
	
	return 0;
}