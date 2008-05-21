/*
 *  Camino.h
 *  Server2Go
 *
 *  Created by Timo Haberkern on 11.08.07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */
#include "WebbrowserHandler.h"

#ifndef __CAMINO_HANDLER_H_
#define __CAMINO_HANDLER_H_

class CaminoHandler: public WebbrowserHandler 
{
public:
	void start(wxString url);

	wxString getProcessName();
	wxString getBundleId();
	
	bool checkAvailability();
};

#endif