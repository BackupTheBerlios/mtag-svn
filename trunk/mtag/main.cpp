// Author: Felix Bechstein <f@ub0r.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>

/* For taglib */
#include <fileref.h>
#include <tag.h>

/* For getopts */
#include <unistd.h>

/* local includes */
#include "meta.h"
#include "utils.h"
#include "db.h"

using namespace std;

void usage(char* arg0)
{
	cout << "mTag: the fast media tag lib" << endl;
	cout << endl;
	cout << "usage: " << arg0 << " [-z path] [-b db] [-a tag] [-d tag] [-c] [-y] [-s] files" << endl;
	cout << "	-b db	database file (default: $MTAG_DB)" <<endl;
	cout << "	-z path	strip leading path (default: $MTAG_STRIPPATH)" <<endl;
	cout << "	-a tag	add tag" <<endl;
	cout << "	-d tag	delete tag" <<endl;
	cout << "	-c	clear tags" <<endl;
	cout << "	-s	show tag (default)" <<endl;
	cout << "	-y dir	sync dir" <<endl;
	cout << "	-x tag	search for tag" <<endl;
	cout << "	-h	show this message" <<endl;
	cout << endl;
	cout << "	-b and -z should be set first" << endl;
}

int main(int argc, char *argv[])
{
	string p;
	if (getenv("MTAG_DB"))
	{
		p = getenv("MTAG_DB");
	} else {
		p = getenv("HOME");
		p += "/.mtag.db";
	}
	sql::setDataBase(p.c_str());
	if (getenv("MTAG_STRIPPATH"))
		utils::setStripPath(getenv("MTAG_STRIPPATH"));
	opterr = 0;
	int optchar;
	bool needusage = true;
	bool show = true;
	bool needshow = false;
	TagLib::StringList foundfiles;
	while ((optchar = getopt(argc, argv, "+b:a:d:chs:y:x:z:")) > 0) {
		switch(optchar)
		{
			case 'b':
				sql::setDataBase(optarg);
				break;
        		case 'a':
				needusage = false;
				show = false;
				for(int i = 1; i < argc; i++)
				{
					meta::addTag(argv[i], optarg);
				}
				break;
			case 'c':
				needusage = false;
				show = false;
				for(int i = 1; i < argc; i++)
				{
					meta::clearTags(argv[i]);
				}
				break;
			case 'd':
				needusage = false;
				show = false;
				for(int i = 1; i < argc; i++)
				{
					meta::delTag(argv[i], optarg);
				}
				break;
			case 's':
				if (argc > 2)
					needusage = false;
				needshow=true;
				break;
			case 'y':
				needusage = false;
				meta::syncdir(optarg);
				break;
			case 'x':
				if (argc > 2)
					needusage = false;
				meta::search(optarg, &foundfiles);
				for (TagLib::StringList::Iterator it = foundfiles.begin(); it != foundfiles.end(); it++)
					cout << utils::stripPath((*it).toCString()) << endl;
				break;
			case 'z':
				utils::setStripPath(optarg);
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
			if (meta::getTags(argv[i], &tags) == EXIT_SUCCESS)
			{
				cout << utils::stripPath(argv[i]) << ": " << tags.toString(", ") << endl;
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
