/*
 *  DirTraverser.h
 *  Server2Go
 *
 *  Created by Timo Haberkern on 29.07.07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#include <wx/dir.h>
#include <wx/filename.h>
#include <wx/filefn.h>
#include <wx/arrstr.h>

class DirTraverser : public wxDirTraverser
{
public:
	DirTraverser(wxArrayString &files, wxArrayString &dirs,
		wxString strPattern = wxEmptyString)
	  : m_arrayFiles(files)
	  , m_arrayDirs(dirs)
	  , m_strPattern(strPattern)
	{ }

	virtual wxDirTraverseResult OnFile(const wxString& filename);
	virtual wxDirTraverseResult OnDir(const wxString& dirname);

private:
	wxString m_strPattern;
	wxArrayString &m_arrayFiles;
	wxArrayString &m_arrayDirs;
};