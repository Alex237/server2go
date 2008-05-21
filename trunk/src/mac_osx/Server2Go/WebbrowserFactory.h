/*
 *  WebserverFactory.h
 *  Server2Go
 *
 *  Created by Timo Haberkern on 11.08.07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __WEBBROWSER_FACTORY_H_
#define __WEBBROWSER_FACTORY_H_

#include "wx/wx.h"
#include "WebbrowserHandler.h"
#include "Configuration.h"

class WebbrowserFactory
{
public:
	WebbrowserHandler* createInstance(Configuration* config);
};

#endif