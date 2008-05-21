/*
 *  WebserverFactory.cpp
 *  Server2Go
 *
 *  Created by Timo Haberkern on 11.08.07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#include "WebbrowserFactory.h"
#include "Configuration.h"
#include "WebbrowserHandler.h"

#include "FirefoxHandler.h"
#include "CaminoHandler.h"
#include "SafariHandler.h"

WebbrowserHandler* WebbrowserFactory::createInstance(Configuration* config)
{
	WebbrowserHandler *handler = NULL;
	
	switch (config->m_nBrowserType)
	{
		case BROWSER_TYPE_FIREFOX:
						handler = new FirefoxHandler();
						if (handler->checkAvailability())
						{
							return handler;
						}
						break;
		case BROWSER_TYPE_CAMINO:
						handler = new CaminoHandler();
						if (handler->checkAvailability())
						{
							return handler;
						}
						break;
		case BROWSER_TYPE_SYSTEM_DEFAULT:
						//--- On MAC using safari as default browser
						//--- so lets fall through
		case BROWSER_TYPE_SAFARI:
						break;
	}
	
	//--- if we get here we need to use Safari
	handler = new SafariHandler();
	
	return handler;
}
