/*
 *  WaitForApache.h
 *  Server2Go
 *
 *  Created by Timo Haberkern on 12.07.07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */
#include <wx/thread.h>
#include <wx/string.h>

class WaitForApache : public wxThread
{
public:
	WaitForApache(wxString hostname, long port, wxMutex *mutex, wxCondition *condition);
	virtual void *Entry();
	
private:
	wxString m_hostname;
	long m_port;
	wxMutex* m_mutex;
	wxCondition* m_condition;
};