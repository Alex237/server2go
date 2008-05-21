/*
 *  FirefoxHandler.h
 *  Server2Go
 *
 *  Created by Timo Haberkern on 11.08.07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */
 #include "WebbrowserHandler.h"

#ifndef __FIREFOX_HANDLER_H_
#define __FIREFOX_HANDLER_H_

class FirefoxHandler: public WebbrowserHandler 
{
public:
	void start(wxString url);
	
	wxString getProcessName();
	wxString getBundleId();
	
	bool checkAvailability();
};

#endif