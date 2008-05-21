/*
 *  AppleEventHelper.cpp
 *  Server2Go
 *
 *  Created by Timo Haberkern on 21.10.07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#include "AppleEventHelper.h"
#include "wx/wx.h"

bool AppleEventHelper::BuildEventByKernelProcessId(long pid, AppleEvent *event)
{
	OSStatus err;
	wxString strpid;
	strpid << pid;
	
	// build Apple event
	err = AEBuildAppleEvent(kAECoreSuite,
							kAEGetData,
							typeKernelProcessID,
							strpid.fn_str(),
							strpid.Length(),
							kAutoGenerateReturnID,
							kAnyTransactionID,
							event,
							NULL,
							"'----':'obj '{form:prop, want:type(prop), seld:type(pnam), from:"
							"'obj '{form:indx, want:type(cwin), seld:abso('all '), from:()}}");
	if (err) return false;
	
	return true;
}

bool AppleEventHelper::BuildEventByBundleId(char *bundleID, AppleEvent *event)
{
	OSStatus err;
	
	// build Apple event
	err = AEBuildAppleEvent(kAECoreSuite,
							kAEGetData,
							typeApplicationBundleID,
							bundleID,
							strlen(bundleID),
							kAutoGenerateReturnID,
							kAnyTransactionID,
							event,
							NULL,
							"'----':'obj '{form:prop, want:type(prop), seld:type(pnam), from:"
							"'obj '{form:indx, want:type(cwin), seld:abso('all '), from:()}}");
	if (err) return false;
	
	return true;
}

int AppleEventHelper::findOpenWindow(char *bundleID)
{
	AppleEvent reply;
	AppleEvent event;
	
	AEDesc listDesc, nameDesc;
	Size nameSize;
	char *name;
	long listLen, i;
	OSStatus err;
	
	// build Apple event
	err = AEBuildAppleEvent(kAECoreSuite,
							kAEGetData,
							typeApplicationBundleID,
							"com.apple.Safari",
							strlen("com.apple.Safari"),
							kAutoGenerateReturnID,
							kAnyTransactionID,
							&event,
							NULL,
							"'----':'obj '{form:prop, want:type(prop), seld:type(pnam), from:"
							"'obj '{form:indx, want:type(cwin), seld:abso('all '), from:()}}");
	if (err) return false;
	
	
	// send Apple event
	err = AESendMessage(&event, &reply, kAEWaitReply, kAEDefaultTimeout);
	AEDisposeDesc(&event);
	if (err) return err;
	
	// get return value from reply event
	err = AEGetParamDesc(&reply,
						 keyAEResult,
						 typeAEList,
						 &listDesc);
	AEDisposeDesc(&reply);
	if (err) return err;
	
	// get each descriptor from list
	err = AECountItems(&listDesc, &listLen);
	if (err) goto cleanup;
	
	/*for (i=0; i<listLen; i++) {
		AEKeyword key;
		err = AEGetNthDesc(&listDesc,
						   i + 1,
						   typeUTF8Text,
						   &key,
						   &nameDesc);
		if (err) goto cleanup;
		
		// get UTF8 text from descriptor
		nameSize = AEGetDescDataSize(&nameDesc);
		name = (char*)malloc(nameSize);
		err = AEGetDescData(&nameDesc,
							name,
							nameSize);
		AEDisposeDesc(&nameDesc);
		if (err) goto cleanup;
		
		// do stuff with it...
		printf("%.*s\n", nameSize, name);
		free(name);
	}*/
	return listLen;
	
cleanup:
		AEDisposeDesc(&listDesc);	
	return -1;
	
	return 0;
}