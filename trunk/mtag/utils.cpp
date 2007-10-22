//
// C++ Implementation: utils
//
// Description: 
//
//
// Author:  Felix Bechstein <f@ub0r.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include <stdlib.h>
#include <string>
#include <sys/param.h>
#include <unistd.h>
#include <fileref.h>
#include <tag.h>

#include "utils.h"

using namespace std;

string utils::absPath(const char* path){
	string p = path;
	if (p.find("/") != 0)
	{
		char cwd[MAXPATHLEN];
		getcwd(cwd, MAXPATHLEN);
		p = "/" + p;
		p = cwd + p;
	}
	uint i;
	while ((i = p.find("//")) != string::npos)
	{
		p.erase(i, 1);
	}
	while ((i = p.find("/./")) != string::npos)
	{
		p.erase(i, 2);
	}
	while ((i = p.find("/../")) != string::npos)
	{
		if (i == 0)
		{
			p.erase(i, 3);
		} else {
			uint j = p.rfind("/", i - 1);
			p.erase(j, 3 + i - j);
		}
	}
	if ((i = p.rfind("/")) == p.length() - 1){
		p.erase(i, 1);
	}
	if ((i = p.find("/.")) == p.length() - 2)
		p.erase(i, 2);
	if ((i = p.find("/..")) == p.length() - 3)
	{
		if (i == 0)
			p = "/";
		else {
			uint j = p.rfind("/", i - 1);
			p.erase(j, 3 + i - j);
		}
	}
	return p;
}

string utils::strippath;

void utils::setStripPath(const char* path)
{
	strippath = absPath(path);
}

string utils::stripPath(const char* path)
{
	string p(path);
	if (! strippath.length())
		return p;
	if (p.find(strippath) == 0)
		p.erase(0, strippath.length() + 1);
	return p;
}
