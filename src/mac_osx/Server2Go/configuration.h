/*
 *  configuration.h
 *  Server2Go
 *
 *  Created by Timo Haberkern on 10.07.07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef __CONFIGURATION__
#define __CONFIGURATION__

#include <wx/fileconf.h> 
#include <wx/filename.h>
#include <wx/wfstream.h>



#define BROWSER_TYPE_CAMINO		1
#define BROWSER_TYPE_FIREFOX		2
#define BROWSER_TYPE_SYSTEM_DEFAULT	4
#define BROWSER_TYPE_SAFARI			8
 
class Configuration
{
	public:
		void loadFromFile (wxString configFile);
		
	public:
		//--- General
		bool		m_bShowStartupProgress;
		bool		m_bShowSplashScreen;
		bool		m_bAllowOnlySingleInstance;
		bool		m_bStartLocal;
		bool		m_bKeepRunningAfterBrowserClose;
		wxString	m_strServerName;
		wxString	m_strSplashScreen;

		//--- Browser
		int			m_nBrowserType;
		
		//--- Http
		wxString	m_strHostName;
		long		m_dwHttpPort;
		wxString	m_strDefaultFile;
		wxString	m_strDefaultRoot;
		
		
		//--- Database
		bool		m_bUseMySQL;
		long		m_dwMySQLPort;
		wxString	m_strMySqlParameter;
		
		bool		m_bLocalMirror;
		bool		m_bDeleteDatabaseFiles;
		bool		m_bOverwriteLocalMirror;
		wxString	m_strMirrorFolder;
		
};

#endif
