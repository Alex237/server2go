/*
 *  ServerStarter.cpp
 *  Server2Go
 *
 *  Created by Timo Haberkern on 12.07.07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#include <wx/socket.h>
#include <wx/thread.h>
#include <wx/wx.h>
#include <wx/filename.h>
#include <wx/utils.h>
#include <wx/process.h>
#include "ServerHandler.h"
#include "ApacheWebserverStarter.h"
#include "MySQLDatabaseStarter.h"
#include "PortHelper.h"
#include "FileHelper.h"
#include "WaitForApache.h"

#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>

bool ServerHandler::StartUpServer (Configuration *config)
{
	this->m_config = config;
	
	//--- IP Address
	wxIPV4address address;
	address.AnyAddress(); 
	wxString ipAddress = address.IPAddress();
	//wxMessageBox(ipAddress);
	
	wxString hostname = wxT("127.0.0.1");
	m_envHost = hostname;
	
	/*char myname[255 + 1];
	int i = gethostname(myname, 255);
	hostent *info = gethostbyname('localhost');
*/
	//wxString hn = myname;
	//MessageBox(myname);
	
	//--- getting temp folder
	wxString tempFolder =  wxFileName::GetHomeDir();
	
	/**
	 * creating / setting the runtime environment
	 */
	wxString pid;
	pid << ::wxGetProcessId();
	
	tempFolder = tempFolder+wxT("/.Server2Go_")+pid+wxT("/");
	m_envRuntimeDir = tempFolder;
	
	wxFileName::Mkdir(tempFolder);
	wxFileName::Mkdir(tempFolder+wxT("session") );
	
	m_envBaseDir = ::wxGetCwd() + wxT("/");
	
	//--- delete the symbolic link /tmp/server2go
	::wxExecute(wxT("rm -f /tmp/server2go"), wxEXEC_ASYNC);
	wxSleep(1);
	
	//--- creating the temporary symbolic link /tmp/server2go
	::wxExecute(wxT("ln -s ") + m_envBaseDir + wxT("server/ /tmp/server2go"), wxEXEC_ASYNC);
	
	m_envServerDir = m_envBaseDir + wxT("server/");
	m_envDocRoot = m_envBaseDir + config->m_strDefaultRoot;
	
	m_envUserName = ::wxGetUserId();
	
	//--- Copy the database files
	if (config->m_bLocalMirror)
	{
		wxString dbdir = wxT("");
		if (config->m_strMirrorFolder.Length() > 0)
		{
			dbdir = config->m_strMirrorFolder + wxT("/");	
		
		}
		else
		{
			dbdir = tempFolder+wxT("dbdir/");
		}
		
		FileHelper::CopyDirRecursive(wxT("dbdir"), dbdir, config->m_bOverwriteLocalMirror);
		m_envDbDir = dbdir;
	
	}
	
	/*
	 * Check for free ports and other network related material
	 * (i.e. ip address)
	 */
	//--- Apache
	long apachePort = PortHelper::getFreeWebserverPort(hostname, this->m_config->m_dwHttpPort);
	m_envApachePort << apachePort;
	
	//wxMessageBox(m_envApachePort);
	
	//--- MySQL
	long mysqlPort = PortHelper::getFreeMySqlPort(hostname, this->m_config->m_dwMySQLPort);
	m_envMyqlPort << mysqlPort;
	
	//wxMessageBox(m_envMyqlPort);
	
	/*
	 * Make copies of the configuration files.
	 * php.ini, my.conf, httpd.conf
	 */
	CopyAndParse(wxT("server/config_tpl/php.ini"), tempFolder+wxT("php.ini"));
	CopyAndParse(wxT("server/config_tpl/my.ini"), tempFolder+wxT("my.ini"));
	CopyAndParse(wxT("server/config_tpl/httpd.conf"), tempFolder+wxT("httpd.conf"));
	
	if (m_config->m_bUseMySQL)
	{
		::wxSetEnv(_T("S2G_EDITION"), _T("PSM"));
	}
	else
	{
	    ::wxSetEnv(_T("S2G_EDITION"), _T("PS"));
	}
	::wxSetEnv(_T("S2G_SERVER_SOFTWARE"), _T("Server2Go (Mac) 1.0.1"));
	::wxSetEnv(_T("S2G_SERVER_APPROOT"), m_envBaseDir);
	::wxSetEnv(_T("S2G_SERVER_DOCROOT"), m_envDocRoot);
	::wxSetEnv(_T("S2G_DB_PATH"), m_envDbDir);
	::wxSetEnv(_T("S2G_TEMP_FOLDER"), tempFolder);
	
	/*
	 * Startup Apache
	 */
	ApacheWebserverStarter objApache;
	m_apache_pid = objApache.StartUp(m_envServerDir, m_envRuntimeDir); 
	 
	/*
	 * Startup MySQL
	 */
	if (m_config->m_bUseMySQL)
	{
		MySQLDatabaseStarter objMySQL;
		m_mysql_pid = objMySQL.StartUp(m_envServerDir, m_envRuntimeDir, mysqlPort, config);
	}
	 
	/*
	 * Wait until both are started up before going further
	 */
	wxMutex mutex;
	wxCondition condition(mutex);
	mutex.Lock();
	
	WaitForApache *apacheWaiter = new WaitForApache (hostname, apachePort, &mutex, &condition);
	if (apacheWaiter->Create() != wxTHREAD_NO_ERROR)
	{
		apacheWaiter->SetPriority(10);
		apacheWaiter->Run();
		
		if (wxCOND_TIMEOUT == condition.WaitTimeout(30000) )
		{
			//--- TODO: Throw Error
		}
	}	
	
	wxSleep(2);
	
	//--- getting the apache pid from pid file if there was no pid as
	//--- a result from from the apache or mysql start
	if (m_apache_pid == 0)
	{
		wxTextFile fileSource;
		fileSource.Open(tempFolder+_T("httpd.pid"));
		if ( fileSource.IsOpened() )
		{
			wxString line = fileSource.GetFirstLine();
			line.ToLong(&m_apache_pid);
		}
	}
	
	if (m_mysql_pid == 0)
	{
		wxTextFile fileSource;
		fileSource.Open(tempFolder+_T("mysql.pid"));
		if ( fileSource.IsOpened() )
		{
			wxString line = fileSource.GetFirstLine();
			line.ToLong(&m_mysql_pid);
		}
	}
	
	return true;
}

bool ServerHandler::ShutDownServer ()
{
	//--- stopping apache server
	//::wxExecute(wxT("/tmp/server2go/library/bin/apachectl stop"), wxEXEC_ASYNC);
	
	wxSleep(2);
	
	if (m_apache_pid > 0)
		wxProcess::Kill(m_apache_pid, wxSIGTERM);
	
	//--- stoping mysql server
	if (m_mysql_pid > 0)
		wxProcess::Kill(m_mysql_pid, wxSIGTERM);
	
	
	//--- delete the temp folder
	wxString pid;
	pid << ::wxGetProcessId();
	
	wxString tempFolder =  wxFileName::GetHomeDir();
	tempFolder = tempFolder+wxT("/.Server2Go_")+pid+wxT("/");
	
	bool result = FileHelper::RmDirRecursive(tempFolder);
	
	//--- delete the symbolic link /tmp/server2go
	::wxExecute(wxT("rm -f /tmp/server2go"), wxEXEC_ASYNC);
	
	return true;
}


bool ServerHandler::CopyAndParse(wxString source, wxString destination)
{
	wxTextFile fileSource(source);
	fileSource.Open();
	wxTextFile fileDestination(destination);
	fileDestination.Create();
	
	if (fileSource.IsOpened() || fileDestination.IsOpened() )
	{
		size_t i;
		wxString line;
		for ( line = fileSource.GetFirstLine(); !fileSource.Eof(); line = fileSource.GetNextLine() )
		{
		    // do something with the current line in str
			
			line.Replace(wxT("%CDPMS:RTDIR%"), m_envRuntimeDir, true);
			line.Replace(wxT("%CDPMS:MYSQLPRT%"), m_envMyqlPort, true);
			line.Replace(wxT("%CDPMS:SRVDIR%"), m_envServerDir, true);
			line.Replace(wxT("%CDPMS:DBDIR%"), m_envDbDir, true);
			line.Replace(wxT("%CDPMS:HOST%"), m_envHost, true);
			line.Replace(wxT("%CDPMS:PORT%"), m_envApachePort, true);
			line.Replace(wxT("%CDPMS:DOCROOT%"), m_envDocRoot, true);
			line.Replace(wxT("%CDPMS:BASEDIR%"), m_envBaseDir, true);
			line.Replace(wxT("%CDPMS:USERNAME%"), m_envUserName, true);
			
			fileDestination.AddLine(line);
		}
		
		fileDestination.Write();
		fileDestination.Close();
		fileSource.Close();
		
		return false;
	}
	
	
}

