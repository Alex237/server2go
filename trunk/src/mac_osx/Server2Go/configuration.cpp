/*
 *  configuration.cpp
 *  Server2Go
 *
 *  Created by Timo Haberkern on 10.07.07.
 *  Copyright 2007 Timo Haberkern. All rights reserved.
 *
 */

#include "configuration.h"

void Configuration::loadFromFile (wxString configFile)
{
	if ( !wxFileName::FileExists( configFile ) ) 
    { 
        // here you'd add code to handle first run...or missing cfg file! 
        //wxMessageBox(_T("The given config file couldn't be read. Starting with default values..."), _T("Server2Go")); 
    } 

    wxFileInputStream ini( configFile ); 
    
    wxFileConfig *pConfig = new wxFileConfig(ini);
	if ( NULL != pConfig )
	{
		this->m_strSplashScreen = pConfig->Read( wxT("/general/UseSplash") , wxT("") );
		this->m_bShowSplashScreen = (this->m_strSplashScreen.Len() != 0);
		
		pConfig->Read (wxT("general/AllowOnlySingleInstance"), this->m_bAllowOnlySingleInstance);
		
		this->m_strServerName = pConfig->Read( wxT("general/ServerName"), wxT("Server2Go") );
		
		this->m_dwHttpPort = pConfig->Read( wxT("http/Port"), 4001);
		this->m_strDefaultRoot = pConfig->Read( wxT("http/DefaultRoot"), wxT("htdocs") );
		this->m_strDefaultFile = pConfig->Read( wxT("http/DefaultFile"), wxT(""));
		
		this->m_bUseMySQL = pConfig->Read( wxT("database/UseMySQL"), true);
		this->m_dwMySQLPort = pConfig->Read( wxT("database/MySQLPort"), 3306);
		this->m_strMySqlParameter = pConfig->Read( wxT("database/MySQLCmd"), wxT(""));
		
		this->m_bLocalMirror = pConfig->Read( wxT("database/LocalMirror"));
		this->m_bDeleteDatabaseFiles = pConfig->Read( wxT("database/DeleteDatabaseFiles"), true);
		this->m_bOverwriteLocalMirror = pConfig->Read( wxT("database/OverwriteLocalMirror"), true);
		this->m_strMirrorFolder = pConfig->Read( wxT("database/MirrorFolder"), wxT(""));
		
		wxString browserType = pConfig->Read( wxT("browser/BrowserType"), _T("SAFARI"));
		if (::wxStricmp(browserType, _T("SAFARI")) == 0) {
			this->m_nBrowserType = BROWSER_TYPE_SAFARI;
		}
		else if (::wxStricmp(browserType, _T("CAMINO")) == 0) {
			this->m_nBrowserType = BROWSER_TYPE_CAMINO;
		}
	} 
     	
}

