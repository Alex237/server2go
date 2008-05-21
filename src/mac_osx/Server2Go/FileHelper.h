/*
 *  FileHelper.h
 *  Server2Go
 *
 *  Created by Timo Haberkern on 29.07.07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */
#include "wx/string.h"

class FileHelper
{
public:
	static bool RmDirRecursive(wxString rmDir);
	static bool CopyDirRecursive(wxString sourceDir, wxString destDir, bool overwrite);
};


