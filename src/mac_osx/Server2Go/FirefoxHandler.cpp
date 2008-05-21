/*
 *  FirefoxHandler.cpp
 *  Server2Go
 *
 *  Created by Timo Haberkern on 11.08.07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#include "FirefoxHandler.h"
#include <wx/utils.h>
#include <wx/file.h>

void FirefoxHandler::start(wxString url)
{
	wxString launchBrowserCmd = wxT("open -a Firefox ") + url;
	
	m_pid = wxExecute (launchBrowserCmd, wxEXEC_ASYNC);
}

wxString FirefoxHandler::getProcessName()
{
	return wxT("Firefox");
}

wxString FirefoxHandler::getBundleId()
{
	return wxT("org.mozilla.Firefox");
}

bool FirefoxHandler::checkAvailability()
{
	return wxFile::Exists(wxT("/Applications/Firefox.app"));
}