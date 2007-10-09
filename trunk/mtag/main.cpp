
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

int getTag(char* filename, vector<TagLib::String> tags)
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
			tags.insert(tags.begin(), thisTag);
			cout << thisTag << endl;
		}
		
	}
	return EXIT_SUCCESS;
}

int addtag(char* filename, char* tag)
{
	TagLib::FileRef f(filename);
	if(!f.isNull() && f.tag())
	{
		TagLib::Tag *tag = f.tag();
		TagLib::String tags = tag->comment();
	}
	return EXIT_SUCCESS;
}

int main(int argc, char *argv[])
{
	opterr = 0;
	int optchar;
	optchar = getopt(argc, argv, "+a:r:cs:");
	
	switch(optchar)
	{
        	case 'a':
			break;
	}


	for(int i = 1; i < argc; i++)
	{
		vector<TagLib::String> tags;
		getTag(argv[i], tags);
		for (int i = 0; i <= tags.size(); i++)
		{
			cout << tags[i] << endl;
		}
	}

	return EXIT_SUCCESS;
}
