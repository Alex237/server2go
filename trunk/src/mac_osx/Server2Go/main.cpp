/*
 *  main.cpp
 *  Server2Go
 *
 *  Created by Timo Haberkern on 10.07.07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

// Grab precompiled headers if possible
#include <wx/wxprec.h>
#include <wx/cmdline.h>
#include <wx/splash.h>
#include <wx/image.h>
#include <wx/snglinst.h>
#include <wx/process.h>

//#include "Configuration.h"
#include "ServerHandler.h"
#include "PortHelper.h"

#include "WebbrowserHandler.h"
#include "SafariHandler.h"
#include "FirefoxHandler.h"
#include "CaminoHandler.h"
#include "WebbrowserFactory.h"

#include "WaitForBrowserClose.h"
#include "ProcessHelper.h"

#include "AppleEventHelper.h"

#include <Carbon/Carbon.h>
 
class Server2GoApp : public wxApp
{
public:
	virtual bool OnInit();
};

DECLARE_APP(Server2GoApp)


IMPLEMENT_APP(Server2GoApp)

bool Server2GoApp::OnInit()
{
	wxInitAllImageHandlers();

    wxString cmdFilename;
	wxString configFilename = wxT("config.ini");
	
	wxSingleInstanceChecker *checker = NULL;
	wxSplashScreen *splash = NULL;
//	wxCmdLineParser cmdParser(g_cmdLineDesc, argc, argv);

	/*
	 * Reading the config data
	 */
	Configuration objConfiguration;
	objConfiguration.loadFromFile( wxT("config.ini") );
	
	if (objConfiguration.m_bAllowOnlySingleInstance == true)
	{
		wxString singleInstanceId = wxString::Format(wxT("%s-%s"), 
										objConfiguration.m_strServerName,
										wxGetUserId().c_str() );
										
		checker = new wxSingleInstanceChecker(singleInstanceId);
		if (checker->IsAnotherRunning())
		{
			//--- TODO: Throw error message
			return false;
		}
	}
	
	/*
	 * Show splash screen if the configiuration parameter is set
	 */
	if (true == objConfiguration.m_bShowSplashScreen)
	{
		//--- Show splash screen
		wxBitmap bitmap;
		if (bitmap.LoadFile( objConfiguration.m_strSplashScreen, wxBITMAP_TYPE_ANY))
		{
			splash = new wxSplashScreen(bitmap,
				  wxSPLASH_CENTRE_ON_SCREEN|wxSPLASH_NO_TIMEOUT,
				  7000, NULL, -1, wxDefaultPosition, wxDefaultSize,
				  wxSIMPLE_BORDER|wxSTAY_ON_TOP);
			
			wxYield(); 
		}
	}
	
	/*
	 * Startup Servers
	 */
	ServerHandler serverHandler;
	bool result = serverHandler.StartUpServer(&objConfiguration);
	if (false == result)
	{
		return -1;
	}
	 
	if (NULL != splash) 
	{
		//--- Close splash screen
		splash->Show(false);
		splash->Close();
		splash->Destroy();
		delete splash;
	} 
	 
	/*
	 * Startup Browser
	 * The rest of the code will processed after the browser is closed
	 */
	WebbrowserHandler* webbrowser;
	
	wxString url = wxT("http://")+serverHandler.m_envHost + wxT(":") + serverHandler.m_envApachePort;
	
	if (objConfiguration.m_strDefaultFile.Length() > 0 )
	{
		url += wxT("/") + objConfiguration.m_strDefaultFile;
	}
	
	//--- Dont know why the hell the factory isn't working, so using a
	//--- simple switch case
	wxString launchBrowserCmd;
	wxString browserProcessName;
	wxString browserBundleId;
	
	WebbrowserFactory factory;
	WebbrowserHandler *handler = factory.createInstance(&objConfiguration);
	
	/*switch (objConfiguration.m_nBrowserType)
	{
		case BROWSER_TYPE_CAMINO:
						launchBrowserCmd = wxT("open -a Camino ") + url;
						browserProcessName = wxT("Camino");
						browserBundleId = wxT("org.mozilla.camino");
						break;
		case BROWSER_TYPE_SYSTEM_DEFAULT:
						//--- On MAC using safari as default browser
						//--- so lets fall through
		case BROWSER_TYPE_SAFARI:
						launchBrowserCmd = wxT("open -a Safari ") + url;
						browserProcessName = wxT("Safari");
						browserBundleId = wxT("com.apple.Safari");
	}
	
	wxExecute(launchBrowserCmd, wxEXEC_ASYNC);*/
	handler->start(url);
	
	wxSleep(2);
	long browser_pid = ProcessHelper::GetPIDForProcessName(browserProcessName.fn_str());
	
	//--- wait for browser close 
	wxMutex mutex;
	wxCondition condition(mutex);
	
	mutex.Lock();
	
	WaitForBrowserClose *browserWaiter = new WaitForBrowserClose (browser_pid, browserBundleId, &mutex, &condition);
	if (browserWaiter->Create() == wxTHREAD_NO_ERROR)
	{
		browserWaiter->SetPriority(10);
		browserWaiter->Run();
		
		condition.Wait();
	}	

	/*
	 * Shutdown Servers 
	 */
	serverHandler.ShutDownServer(); 
	
	if (NULL != checker)
	{
		delete checker;
	}
	
	::wxExit();
	
	return true;
}

