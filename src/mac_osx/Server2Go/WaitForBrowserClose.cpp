/*
 *  WaitForBrowserClose.cpp
 *  Server2Go
 *
 *  Created by Timo Haberkern on 14.10.07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#include "WaitForBrowserClose.h"
#include <wx/wx.h>
#include "ProcessHelper.h"
#include "AppleEventHelper.h"

WaitForBrowserClose::WaitForBrowserClose(long browser_pid, wxString browserBundleId, wxMutex *mutex, wxCondition *condition)
{
	m_browser_pid = browser_pid;
	m_mutex = mutex;
	m_condition = condition;
	m_browserBundleId = browserBundleId;
}

void *WaitForBrowserClose::Entry()
{
	bool bStop = false;
	
	AppleEventHelper eventHelper;
//	AppleEvent event;
//	eventHelper.BuildEventByBundleId((char*)m_browserBundleId.c_str(), &event);
	
	while (bStop == false)
	{
	//	int nCount = eventHelper.findOpenWindow(&event);
		
		bStop = eventHelper.findOpenWindow((char*)m_browserBundleId.c_str()) <= 0;
		//bStop = !ProcessHelper::PidExists(m_browser_pid);
		Sleep(500);
	}
	
	wxMutexLocker lock(*m_mutex);
	m_condition->Broadcast();
	
	return NULL;
}