/*
 *  SafarieHandler.cpp
 *  Server2Go
 *
 *  Created by Timo Haberkern on 12.08.07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#include <wx/wx.h>
#include "SafariHandler.h"

void SafariHandler::start(wxString url)
{
	wxString launchBrowserCmd = wxT("open -a Safari ") + url;
	m_pid = wxExecute ( launchBrowserCmd, wxEXEC_ASYNC);
}

wxString SafariHandler::getProcessName()
{
	return wxT("Safari");
}

wxString SafariHandler::getBundleId()
{
	return wxT("com.apple.Safari");
}

bool SafariHandler::checkAvailability()
{
	return true; //--- Safari is always available on MAC systems
}