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

using namespace std;

int getTags(char* filename, vector<TagLib::String> *tags)
{
	TagLib::FileRef f(filename);
	if(!f.isNull() && f.tag())
	{
		TagLib::Tag *tag = f.tag();
		TagLib::String sTags = tag->comment();
		if (!tags)
			return EXIT_SUCCESS;
		int tagStart = 0;
		while ((tagStart = sTags.find("tag:", tagStart)) >= 0)
		{
			tagStart += 4;
			int tagEnd = sTags.find(",", tagStart);
			if (tagEnd < 0) tagEnd = 0xffffffff;
			TagLib::String thisTag = sTags.substr(tagStart, tagEnd - tagStart);
			tags->insert(tags->end(), thisTag);
		}
		return EXIT_SUCCESS;
	}
	return -1;
}

int setTags(char* filename, vector<TagLib::String> *tags)
{
	TagLib::FileRef f(filename);
	if(!f.isNull() && f.tag())
	{
		TagLib::Tag *tag = f.tag();

		TagLib::String sTags;
		if (tags)
		{
			for (vector<TagLib::String>::iterator it = tags->begin(); it!=tags->end(); ++it)
			{
				if (it != tags->begin())
					sTags.append(", ");
				sTags.append("tag:");
				sTags.append(*it);
			}
		}
		tag->setComment(sTags);
		f.save();
		return EXIT_SUCCESS;
	}
	return -1;
}

int clearTags(char* filename)
{
	setTags(filename, NULL);
}