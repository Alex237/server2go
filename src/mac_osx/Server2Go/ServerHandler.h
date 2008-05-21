/*
 *  ServerStarter.h
 *  Server2Go
 *
 *  Created by Timo Haberkern on 12.07.07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */
#include "Configuration.h" 

class ServerHandler
{
	public: 
		bool StartUpServer (Configuration *config);
		bool ShutDownServer ();
		
	private:
		bool CopyAndParse(wxString source, wxString destination);
		
	public:
		Configuration *m_config;
		
		wxString	m_envDocRoot;
		wxString	m_envHost;
		wxString	m_envDbDir;
		wxString	m_envServerDir;
		wxString	m_envRuntimeDir;
		wxString	m_envMyqlPort;
		wxString	m_envApachePort;
		wxString	m_envBaseDir;
		wxString	m_envUserName;
		
		long		m_apache_pid;
		long		m_mysql_pid;
		
};
