/*
 *  WaitForBrowserClose.h
 *  Server2Go
 *
 *  Created by Timo Haberkern on 14.10.07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */
#include <wx/thread.h>
#include <wx/string.h>

class WaitForBrowserClose : public wxThread
{
public:
	WaitForBrowserClose(long browser_pid, wxString browserBundleId, wxMutex *mutex, wxCondition *condition);
	virtual void *Entry();
	
private:
	long m_browser_pid;
	wxMutex* m_mutex;
	wxCondition* m_condition;
	wxString m_browserBundleId;
};
