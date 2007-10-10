
#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdio.h>
#include <stdlib.h>

/* For taglib */
#include <fileref.h>
#include <tag.h>

/* For getopts */
#include <unistd.h>
//#include <getopt.h>

/* For sqlite */
#include <sqlite3.h>

using namespace std;

int getTags(char* filename, vector<TagLib::String> *tags)
{
	TagLib::FileRef f(filename);
	if(!f.isNull() && f.tag())
	{
		TagLib::Tag *tag = f.tag();
		TagLib::String sTags = tag->comment();

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
		for (vector<TagLib::String>::iterator it = tags->begin(); it!=tags->end(); ++it)
		{
			if (it != tags->begin())
				sTags.append(", ");
			sTags.append("tag:");
			sTags.append(*it);
		}

		tag->setComment(sTags);
		f.save();

		return EXIT_SUCCESS;
	}
	return -1;
}

int main(int argc, char *argv[])
{
	opterr = 0;
	int optchar;
	optchar = getopt(argc, argv, "+a:r:cs:");
	
	switch(optchar)
	{
        	case 'a':
			for(int i = 1; i < argc; i++)
			{
				vector<TagLib::String> tags;
				if (getTags(argv[i], &tags) < 0)
					continue;
				tags.insert(tags.end(), optarg);
				setTags(argv[i], &tags);
			}
			break;
	}


	for(int i = 1; i < argc; i++)
	{
		vector<TagLib::String> tags;
		if (getTags(argv[i], &tags) < 0)
			continue;
		cout << "track: " << argv[i] << endl;
		cout << "tags: ";
		for (vector<TagLib::String>::iterator it = tags.begin(); it!=tags.end(); ++it)
		{
			if (it != tags.begin())
				cout << ", ";
			cout << *it;
		}
		cout << endl;
	}

	return EXIT_SUCCESS;
}
