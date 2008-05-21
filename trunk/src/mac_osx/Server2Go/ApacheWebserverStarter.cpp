/*
 *  ApacheWebserverStarter.cpp
 *  Server2Go
 *
 *  Created by Timo Haberkern on 12.07.07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#include "ApacheWebserverStarter.h"
#include <wx/wx.h>
#include <wx/process.h>

ApacheWebserverStarter::ApacheWebserverStarter()
{

}

long ApacheWebserverStarter::StartUp(wxString serverpath, wxString temppath)
{
	/*wxString strLibPath;
	wxGetEnv(_T("DYLD_LIBRARY_PATH"), &strLibPath);
	wxMessageBox(strLibPath, _T("environment"));
	*/
	
	wxString startpath = serverpath+ wxT("library/bin/httpd -f ") + temppath + wxT("httpd.conf");	
	
	//wxMessageBox(startpath);
	
	wxProcess *process_info;
	process_info =  wxProcess::Open(startpath);
	
	//--- wxMAC seems not to implement the GetPid method!?!!?? So return 0 to the caller
	return 0;
}