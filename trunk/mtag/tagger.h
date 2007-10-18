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

using namespace std;

int getTags(char* filename, vector<TagLib::String> *tags);
int setTags(char* filename, vector<TagLib::String> *tags);
int clearTags(char* filename);
