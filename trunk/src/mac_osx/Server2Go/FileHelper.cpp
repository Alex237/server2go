/*
 *  FileHelper.cpp
 *  Server2Go
 *
 *  Created by Timo Haberkern on 29.07.07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#include "FileHelper.h"
#include <wx/wx.h>
#include "DirTraverser.h"

bool FileHelper::RmDirRecursive(wxString rmDir) 
{
	wxArrayString files, dirs;
	
	wxDir dir(rmDir);
	DirTraverser traverser(files, dirs);
	dir.Traverse(traverser);
	
	for(size_t i=0; i<files.Count(); i++)
	{
		::wxRemoveFile(files.Item(i));
	}
	
	for(size_t i=0; i<dirs.Count(); i++)
	{
		FileHelper::RmDirRecursive(dirs.Item(i));
	}
	
	::wxRmdir(rmDir);
} 

bool FileHelper::CopyDirRecursive(wxString sourceDir, wxString destDir, bool overwrite)
{
	if (!wxDirExists(destDir))
	{
		::wxMkdir(destDir);
	}
	
	wxArrayString files, dirs;
	
	wxDir dir(sourceDir);
	DirTraverser traverser(files, dirs);
	dir.Traverse(traverser);
	
	for(size_t i=0; i<dirs.Count(); i++)
	{
		wxString dest = dirs.Item(i);
		dest.Replace(sourceDir, destDir);
		::wxMkdir(dest);
		
		FileHelper::CopyDirRecursive(dirs.Item(i), dest, overwrite);
	}
	
	
	for(size_t i=0; i<files.Count(); i++)
	{
		wxString dest = files.Item(i);
		dest.Replace(sourceDir, destDir);
	
		::wxCopyFile(files.Item(i), dest, overwrite);
	}
	
	
}