/*
 *  IWebbrowser.h
 *  Server2Go
 *
 *  Created by Timo Haberkern on 11.08.07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */
 
#ifndef __WEBBROWSER_HANDLER_H_
#define __WEBBROWSER_HANDLER_H_

 #include <wx/object.h>
 
class WebbrowserHandler
{
public:	
	virtual void start(wxString url);
	
	virtual wxString getProcessName();
	virtual wxString getBundleId();
	
	virtual bool checkAvailability();
	
protected:
	long m_pid;
};

#endif