//
// C++ Implementation: tagger
//
// Description: 
//
//
// Author: Felix Bechstein <f@ub0r.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//


#ifdef HAVE_CONFIG_H
#include <config.h>
#endif


#include <stdlib.h>

/* For taglib */
#include <fileref.h>
#include <tag.h>
#include <tstringlist.h>

using namespace std;

int getTags(char* filename, TagLib::StringList *tags)
{
	TagLib::FileRef f(filename);
	if(!f.isNull() && f.tag())
	{
		TagLib::Tag *tag = f.tag();
		TagLib::String sTags = tag->comment();
		if (tags == NULL)
		{
			return EXIT_SUCCESS;
		}
		int tagStart = 0;
		while ((tagStart = sTags.find("tag:", tagStart)) >= 0)
		{
			tagStart += 4;
			int tagEnd = sTags.find(",", tagStart);
			if (tagEnd < 0) tagEnd = 0xffffffff;
			TagLib::String thisTag = sTags.substr(tagStart, tagEnd - tagStart);
			tags->append(thisTag);
		}
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}

int setTags(char* filename, TagLib::StringList tags)
{
	TagLib::FileRef f(filename);
	if(!f.isNull() && f.tag())
	{
		TagLib::Tag *tag = f.tag();

		TagLib::String sTags;
		try {
			if (!tags.isEmpty())
			{
				sTags.append("tag:");
				sTags.append(tags.toString(", tag:"));
			}
		} catch (int e) {
			delete tag;
			return EXIT_FAILURE;
		}
		tag->setComment(sTags);
		f.save();
		return EXIT_SUCCESS;
	}
	return EXIT_FAILURE;
}

int clearTags(char* filename)
{
	setTags(filename, TagLib::StringList());
}
