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
#include <getopt.h>

/* local includes */
#include "config.h"
#include "meta.h"
#include "utils.h"
#include "sql.h"

using namespace std;

void usage(char* arg0)
{
	cout << "mTag: the fast media tag lib" << endl;
	cout << "version: " << VERSION << endl;
	cout << endl;
	cout << "usage: " << arg0 << " [-012345chlsvy] [-ad tag] [-b db] [-z path] files" << endl;
	cout << "	-0			clear rating" << endl;
	cout << "	-12345			set rating" << endl;
	cout << "	-l/--list		list all tags" << endl;
	cout << "	-a/--add tag		add tag" << endl;
	cout << "	-d/--delete tag		delete tag" << endl;
	cout << "	-c/--clear		clear tags" << endl;
	cout << "	-s/--show		show tag (default)" << endl;
	cout << "	-x/--search tag		search for tag" << endl;
	cout << "	-y/--sync dir		sync dir" << endl;
	cout << "	-v/--verbose		verbose" << endl;
	cout << "	-b/--database db	database file (default: $MTAG_DB)" << endl;
	cout << "	-z/--strip path		strip leading path (default: $MTAG_STRIPPATH)" << endl;
	cout << "	--version		print version" << endl;
	cout << "	-h/--help		show this message" << endl;
}

int main(int argc, char *argv[])
{
	utils::setVerbose(false);
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
	int long_index;
	bool needusage = true;
	bool show = true;
	bool needshow = false;
	TagLib::StringList foundfiles;
	TagLib::StringList tags;
	
	const char *optstring = ":012345a:b:cd:hlqsvx:y:z:";
	
	static struct option long_options[] = {
		{"version", no_argument, NULL, 'q'},
		{"add", required_argument, NULL, 'a'},
		{"database", required_argument, NULL, 'b'},
		{"clear", required_argument, NULL, 'c'},
		{"delete", required_argument, NULL, 'd'},
		{"help", no_argument, NULL, 'h'},
		{"list", no_argument, NULL, 'l'},
		{"show", no_argument, NULL, 's'},
		{"verbose", no_argument, NULL, 'v'},
		{"search", required_argument, NULL, 'x'},
		{"sync", required_argument, NULL, 'y'},
		{0, 0, 0, 0}
	};
	
	/* 
		split getopt into two phases:
		1) get env setting options
		2) do work
	*/
	
	while ((optchar = getopt_long(argc, argv, optstring, long_options, &long_index)) > 0) {
		switch(optchar)
		{
			case 'b':
				sql::setDataBase(optarg);
				break;
			case 'q':
				cout << argv[0] << " version: " << VERSION << endl;
				return EXIT_SUCCESS;
			case 'v':
				utils::setVerbose(true);
				break;
			case 'z':
				utils::setStripPath(optarg);
				break;
			case ':':
				usage(argv[0]);
				return EXIT_FAILURE;
				break;
		}
	}
	optind = 0; // restart getopt
	while ((optchar = getopt_long(argc, argv, optstring, long_options, &long_index)) > 0) {
		TagLib::StringList tags2clear;
		switch(optchar)
		{
			case '0':
				utils::vout("clear rate");
				needusage = false;
				show = false;
				tags2clear.append("1");
				tags2clear.append("2");
				tags2clear.append("3");
				tags2clear.append("4");
				tags2clear.append("5");
				for(int i = 2; i < argc; i++)
				{
					meta::delTag(argv[i], tags2clear);
					
				}
				break;
			case '1':
				utils::vout("rate: 1");
				needusage = false;
				show = false;
				tags2clear.append("2");
				tags2clear.append("3");
				tags2clear.append("4");
				tags2clear.append("5");
				for(int i = 2; i < argc; i++)
				{
					meta::delTag(argv[i], tags2clear);
					meta::addTag(argv[i], "1");
					
				}
				break;
			case '2':
				utils::vout("rate: 2");
				needusage = false;
				show = false;
				tags2clear.append("1");
				tags2clear.append("3");
				tags2clear.append("4");
				tags2clear.append("5");
				for(int i = 2; i < argc; i++)
				{
					meta::delTag(argv[i], tags2clear);
					meta::addTag(argv[i], "2");
					
				}
				break;
			case '3':
				utils::vout("rate: 3");
				needusage = false;
				show = false;
				tags2clear.append("1");
				tags2clear.append("2");
				tags2clear.append("4");
				tags2clear.append("5");
				for(int i = 2; i < argc; i++)
				{
					meta::delTag(argv[i], tags2clear);
					meta::addTag(argv[i], "3");
					
				}
				break;
			case '4':
				utils::vout("rate: 4");
				needusage = false;
				show = false;
				tags2clear.append("1");
				tags2clear.append("2");
				tags2clear.append("3");
				tags2clear.append("5");
				for(int i = 2; i < argc; i++)
				{
					meta::delTag(argv[i], tags2clear);
					meta::addTag(argv[i], "4");
					
				}
				break;
			case '5':
				utils::vout("rate: 5");
				needusage = false;
				show = false;
				tags2clear.append("1");
				tags2clear.append("2");
				tags2clear.append("3");
				tags2clear.append("4");
				for(int i = 2; i < argc; i++)
				{
					meta::delTag(argv[i], tags2clear);
					meta::addTag(argv[i], "5");
					
				}
				break;
			case 'a':
				utils::vout("add tag");
				needusage = false;
				show = false;
				for(int i = 3; i < argc; i++)
				{
					meta::addTag(argv[i], optarg);
				}
				break;
			case 'c':
				utils::vout("clear tags");
				needusage = false;
				show = false;
				for(int i = 2; i < argc; i++)
				{
					meta::clearTags(argv[i]);
				}
				break;
			case 'd':
				utils::vout("del tag");
				needusage = false;
				show = false;
				for(int i = 3; i < argc; i++)
				{
					meta::delTag(argv[i], optarg);
				}
				break;
			case 'h':
				utils::vout("help");
				usage(argv[0]);
				return EXIT_SUCCESS;
				break;
			case 'l':
				utils::vout("list tags");
				needusage = false;
				meta::list(&tags);
				cout << tags.toString("\n") << endl;
				break;
			case 's':
				utils::vout("show tags");
				needusage = false;
				needshow=true;
				break;
			case 'x':
				utils::vout("search tags");
				needusage = false;
				meta::search(optarg, &foundfiles);
				for (TagLib::StringList::Iterator it = foundfiles.begin(); it != foundfiles.end(); it++)
					cout << utils::stripPath((*it).toCString()) << endl;
				break;
			case 'y':
				utils::vout("sync tags");
				needusage = false;
				meta::syncdir(optarg);
				break;
			case ':':
				usage(argv[0]);
				return EXIT_FAILURE;
				break;
			case '?':
				usage(argv[0]);
				return EXIT_FAILURE;
				break;
		}
	}
		
	if (show || needshow)
	{
		for(int i = optind; i < argc; i++)
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
