//
// C++ Interface: tagger
//
// Description: 
//
//
// Author: Felix Bechstein <f@ub0r.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include <stdlib.h>

/* For taglib */
#include <fileref.h>
#include <tag.h>
#include <tstringlist.h>

using namespace std;

int getTags(char* filename, TagLib::StringList *tags);
int setTags(char* filename, TagLib::StringList tags);
int clearTags(char* filename);
