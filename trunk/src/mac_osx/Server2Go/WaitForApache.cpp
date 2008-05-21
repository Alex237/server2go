/*
 *  WaitForApache.cpp
 *  Server2Go
 *
 *  Created by Timo Haberkern on 12.07.07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#include "WaitForApache.h"
#include "PortHelper.h"

WaitForApache::WaitForApache(wxString hostname, long port, wxMutex *mutex, wxCondition *condition)
{
	m_hostname = hostname;
	m_port = port;
	m_mutex = mutex;
	m_condition = condition;
}

void *WaitForApache::Entry()
{
	bool bStop = false;
	
	while (bStop == false)
	{
		bStop = !PortHelper::checkPort(m_hostname, m_port);
		Sleep(500);
	}
	
	wxMutexLocker lock(*m_mutex);
	m_condition->Broadcast();
	
	return NULL;
}