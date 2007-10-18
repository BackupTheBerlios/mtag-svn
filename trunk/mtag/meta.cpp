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

using namespace std;

int meta_getTags(char* filename, vector<TagLib::String> *tags)
{
	return getTags(filename, tags);
}

int meta_setTags(char* filename, vector<TagLib::String> *tags)
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
	vector<TagLib::String> tags;
	if (meta_getTags(filename, &tags) != EXIT_SUCCESS)
		return EXIT_FAILURE;
	tags.insert(tags.end(), optarg);
	return meta_setTags(filename, &tags);
}

int meta_delTag(char* filename, TagLib::String tag)
{
	vector<TagLib::String> tags;
	if (meta_getTags(filename, &tags) != EXIT_SUCCESS)
		return EXIT_FAILURE;
	
	return meta_setTags(filename, &tags);
}