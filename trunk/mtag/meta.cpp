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
#include <unistd.h>
#include "tagger.h"
#include "db.h"
#include "utils.h"

/* For taglib */
#include <fileref.h>
#include <tag.h>
#include <tstringlist.h>

/* For sqlite3 */
#include <sqlite3.h>

/* For fs */
#include <sys/types.h>
#include <dirent.h>

#include "meta.h"

using namespace std;

int meta::getTags(char* filename, TagLib::StringList *tags)
{
	return tagger::getTags(filename, tags);
}

int meta::setTags(char* filename, TagLib::StringList tags)
{
	sqlite3 *db;
	if (sql::openDB(&db) != EXIT_SUCCESS)
		return tagger::setTags(filename, tags);
	string ap = utils::absPath(filename);
	sql::clearTags(ap.c_str(), db);
	cout << ap << endl;
	for (TagLib::StringList::Iterator it = tags.begin(); it != tags.end(); it++)
		sql::addTag(ap.c_str(), (*it).toCString(), db);
	sql::closeDB(db);
	return tagger::setTags(filename, tags);
}

int meta::clearTags(char* filename)
{
	if (getTags(filename, NULL) == EXIT_SUCCESS)
	{
		string ap = utils::absPath(filename);
		sql::clearTags(ap.c_str());
		return tagger::clearTags(filename);
	}
	return EXIT_FAILURE;
}

int meta::addTag(char* filename, TagLib::String tag)
{
	TagLib::StringList tags;
	if (getTags(filename, &tags) != EXIT_SUCCESS)
		return EXIT_FAILURE;
	if (tags.find(tag) == tags.end())
		tags.append(tag);
	return setTags(filename, tags);
}

int meta::delTag(char* filename, TagLib::String tag)
{
	TagLib::StringList tags;
	if (getTags(filename, &tags) != EXIT_SUCCESS)
		return EXIT_FAILURE;
	TagLib::StringList::Iterator it = tags.find(tag);
	if (it != tags.end())
		tags.erase(it);
	return setTags(filename, tags);
}

int meta::syncdir(const char *dirname, sqlite3* db)
{
	DIR *dir;
	struct dirent *entry;
	if (!(dir = opendir(dirname))) {
		TagLib::StringList tags;
		if (tagger::getTags(dirname, &tags) == EXIT_SUCCESS)
		{
			if (!tags.isEmpty())
			{
				cout << utils::stripPath(dirname) << ": " << tags << endl;
				string ap = utils::absPath(dirname);
				sql::clearTags(ap.c_str(), db);
				for (TagLib::StringList::Iterator it = tags.begin(); it != tags.end(); it++)
				{
					sql::addTag(ap.c_str(), (*it).toCString(), db);
				}
			}
			return EXIT_SUCCESS;
		}
		return EXIT_FAILURE;
	}

	string sdirname(dirname);
	while ((entry=readdir(dir))) {
		string s(entry->d_name);
		if (s != string(".") && s != string(".."))
		{
			syncdir((sdirname + "/" + entry->d_name).c_str(), db);
		}
	}
	closedir(dir);
	return EXIT_SUCCESS;
}


int meta::syncdir(const char *dirname)
{
	sqlite3* db;
	if(sql::openDB(&db) != EXIT_SUCCESS)
	{
		cerr << "databaseerror" << endl;
		return EXIT_FAILURE;
	}
	string ap = utils::absPath(dirname);
	sql::wipePath(ap.c_str(), db);
	int res = syncdir(ap.c_str(), db);
	sql::closeDB(db);
	return res;
}



int meta::search(const char *tag, TagLib::StringList *files)
{
	return sql::search(tag, files);
}
