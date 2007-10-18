//
// C++ Implementation: meta
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
#include "tagger.h"

/* For taglib */
#include <fileref.h>
#include <tag.h>
#include <tstringlist.h>

using namespace std;

int meta_getTags(char* filename, TagLib::StringList *tags)
{
	return getTags(filename, tags);
}

int meta_setTags(char* filename, TagLib::StringList tags)
{
	return setTags(filename, tags);
}

int meta_clearTags(char* filename)
{
	if (meta_getTags(filename, NULL) == EXIT_SUCCESS)
		return clearTags(filename);
	return EXIT_FAILURE;
}

int meta_addTag(char* filename, TagLib::String tag)
{
	TagLib::StringList tags;
	if (meta_getTags(filename, &tags) != EXIT_SUCCESS)
		return EXIT_FAILURE;
	tags.append(optarg);
	return meta_setTags(filename, tags);
}

int meta_delTag(char* filename, TagLib::String tag)
{
	TagLib::StringList tags;
	if (meta_getTags(filename, &tags) != EXIT_SUCCESS)
		return EXIT_FAILURE;
	TagLib::StringList::Iterator it = tags.find(tag);
	if (it != tags.end())
		tags.erase(it);
	return meta_setTags(filename, tags);
}
