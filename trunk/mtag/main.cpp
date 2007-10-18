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
//#include <getopt.h>

/* For sqlite */
#include <sqlite3.h>

/* local includes */
#include "meta.h"
#include "crawler.h"
#include "db.h"

using namespace std;

int main(int argc, char *argv[])
{
	opterr = 0;
	int optchar;
	optchar = getopt(argc, argv, "+a:r:cs:");
	
	switch(optchar)
	{
        	case 'a':
			for(int i = 2; i < argc; i++)
			{
				meta_addTag(argv[i], optarg);
			}
			break;
		case 'c':
			for(int i = 1; i < argc; i++)
			{
				meta_clearTags(argv[i]);
			}
			break;
		case 'r':
			for(int i = 2; i < argc; i++)
			{
				meta_delTag(argv[i], optarg);
			}
			break;
	}


	for(int i = 1; i < argc; i++)
	{
		vector<TagLib::String> tags;
		if (meta_getTags(argv[i], &tags) < 0)
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
