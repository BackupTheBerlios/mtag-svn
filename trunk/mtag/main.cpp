// Author: Felix Bechstein <f@ub0r.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//
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

/* local includes */
#include "meta.h"

using namespace std;

void usage(char* arg0)
{
	cout << "usage: " << arg0 << " [-a tag] [-d tag] [-c] [-y] [-s] files" << endl;
	cout << "	-a tag	add tag" <<endl;
	cout << "	-d tag	delete tag" <<endl;
	cout << "	-c	clear tags" <<endl;
	cout << "	-s	show tag (default)" <<endl;
	cout << "	-y dir	sync dir" <<endl;
	cout << "	-x tag	search for tag" <<endl;
	cout << "	-h	show this message" <<endl;
	
}

int main(int argc, char *argv[])
{
	opterr = 0;
	int optchar;
	bool needusage = true;
	bool show = true;
	bool needshow = false;
	TagLib::StringList foundfiles;
	while ((optchar = getopt(argc, argv, "+a:d:chs:y:x:")) > 0) {
		switch(optchar)
		{
        		case 'a':
				needusage = false;
				show = false;
				for(int i = 1; i < argc; i++)
				{
					meta_addTag(argv[i], optarg);
				}
				break;
			case 'c':
				needusage = false;
				show = false;
				for(int i = 1; i < argc; i++)
				{
					meta_clearTags(argv[i]);
				}
				break;
			case 'd':
				needusage = false;
				show = false;
				for(int i = 1; i < argc; i++)
				{
					meta_delTag(argv[i], optarg);
				}
				break;
			case 's':
				if (argc > 2)
					needusage = false;
				needshow=true;
				break;
			case 'y':
				needusage = false;
				meta_syncdir(optarg);
				break;
			case 'x':
				if (argc > 2)
					needusage = false;
				meta_search(optarg, &foundfiles);
				cout << foundfiles.toString("\n") << endl;
				break;
			case 'h':
				usage(argv[0]);
				return EXIT_SUCCESS;
				break;
		}
	}
	if (show || needshow)
	{
		for(int i = 1; i < argc; i++)
		{
			TagLib::StringList tags;
			if (meta_getTags(argv[i], &tags) == EXIT_SUCCESS)
			{
				cout << "track: " << argv[i] << endl;
				cout << "tags: " << tags.toString(", ") << endl;
			}
		needusage = false;
		}
	}
	if (needusage || opterr)
	{
		usage(argv[0]);
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
