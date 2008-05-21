/*
 *  AppleEventHelper.h
 *  Server2Go
 *
 *  Created by Timo Haberkern on 21.10.07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#if !defined(__APPLEEVENT_HELPER__)
#define __APPLEEVENT_HELPER__ 1

#include <Carbon/Carbon.h>

class AppleEventHelper
{
public:
	int findOpenWindow(char *bundleID);
	bool BuildEventByBundleId(char *bundleID, AppleEvent *event);
	bool BuildEventByKernelProcessId(long pid, AppleEvent *event);
};

#endif

