/*
 *  DirTraverser.cpp
 *  Server2Go
 *
 *  Created by Timo Haberkern on 29.07.07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

#include "DirTraverser.h"

wxDirTraverseResult DirTraverser::OnFile(const wxString& filename)
{
	if(m_strPattern != wxEmptyString)
	{
		if(::wxMatchWild(m_strPattern, filename, false))
			m_arrayFiles.Add(filename);
	}
	else
	{
		m_arrayFiles.Add(filename);
	}
	return wxDIR_CONTINUE;
}

wxDirTraverseResult DirTraverser::OnDir(const wxString& dirname)
{
	m_arrayDirs.Add(dirname);
	return wxDIR_CONTINUE;
}
