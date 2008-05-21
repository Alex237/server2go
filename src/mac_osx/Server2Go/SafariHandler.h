/*
 *  SafarieHandler.h
 *  Server2Go
 *
 *  Created by Timo Haberkern on 12.08.07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */
#include "WebbrowserHandler.h"

#ifndef __SAFARI_HANDLER_H_
#define __SAFARI_HANDLER_H_



class SafariHandler: public WebbrowserHandler 
{
public:
	void start(wxString url);
	
	wxString getProcessName();
	wxString getBundleId();
	
	bool checkAvailability();
};

#endif