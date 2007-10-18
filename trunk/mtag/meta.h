//
// C++ Interface: meta
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

int meta_getTags(char* filename, TagLib::StringList *tags);
int meta_setTags(char* filename, TagLib::StringList tags);
int meta_clearTags(char* filename);

int meta_addTag(char* filename, TagLib::String tag);
int meta_delTag(char* filename, TagLib::String tag);