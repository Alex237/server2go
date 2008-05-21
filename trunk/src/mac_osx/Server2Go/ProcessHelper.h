/*
 *  ProcessHelper.h
 *  Server2Go
 *
 *  Created by Timo Haberkern on 14.10.07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#if !defined(__PROCESS_HELPER__)
#define __PROCESS_HELPER__ 1

#include <stdlib.h>
#include <stdio.h>

// --- Defining constants for use with sample code --- //
enum  {kSuccess = 0,
	kCouldNotFindRequestedProcess = -1, 
	kInvalidArgumentsError = -2,
	kErrorGettingSizeOfBufferRequired = -3,
	kUnableToAllocateMemoryForBuffer = -4,
	kPIDBufferOverrunError = -5};

class ProcessHelper
{
public:
	static int GetAllPIDsForProcessName(const char* ProcessName,
							 pid_t ArrayOfReturnedPIDs[],
							 const unsigned int NumberOfPossiblePIDsInArray,
							 unsigned int* NumberOfMatchesFound,
							 int* SysctlError); //Can be NULL

	static int GetPIDForProcessName(const char* ProcessName);
	static bool PidExists(int pid);

};
#endif