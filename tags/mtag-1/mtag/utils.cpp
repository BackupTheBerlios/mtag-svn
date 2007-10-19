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
	return p;
}
