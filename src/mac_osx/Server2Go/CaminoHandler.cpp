/*
 *  Camino.cpp
 *  Server2Go
 *
 *  Created by Timo Haberkern on 29.10.07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#include "CaminoHandler.h"
#include <wx/utils.h>
#include <wx/file.h>

void CaminoHandler::start(wxString url)
{
	wxString launchBrowserCmd = wxT("open -a Camino ") + url;
	
	m_pid = wxExecute (launchBrowserCmd, wxEXEC_ASYNC);
}

wxString CaminoHandler::getProcessName()
{
	return wxT("Camino");
}

wxString CaminoHandler::getBundleId()
{
	return wxT("org.mozilla.Camino");
}

bool CaminoHandler::checkAvailability()
{
	return wxFile::Exists(wxT("/Applications/Camino.app"));
}