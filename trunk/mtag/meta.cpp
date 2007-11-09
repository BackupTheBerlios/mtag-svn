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
#include "sql.h"
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

int meta::addTag(char* filename, TagLib::StringList tag)
{
	utils::vout("add tags");
	TagLib::StringList tags;
	if (getTags(filename, &tags) != EXIT_SUCCESS)
		return EXIT_FAILURE;
	bool changed = false;
	for (TagLib::StringList::Iterator it1 = tag.begin(); it1 != tag.end(); it1++)
	{
		if (tags.find(*it1) == tags.end())
		{
			changed = true;
			tags.append(*it1);
		}
	}
	if (!changed)
		return EXIT_SUCCESS;
	return setTags(filename, tags);
}

int meta::addTag(char* filename, TagLib::String tag)
{
	utils::vout("add tag");
	TagLib::StringList tag1;
	tag1.append(tag);
	return addTag(filename, tag1);
}

int meta::delTag(char* filename, TagLib::StringList tag)
{
	utils::vout("del tags");
	TagLib::StringList tags;
	if (getTags(filename, &tags) != EXIT_SUCCESS)
		return EXIT_FAILURE;
	bool changed = false;
	for (TagLib::StringList::Iterator it1 = tag.begin(); it1 != tag.end(); it1++)
	{
		TagLib::StringList::Iterator it = tags.find(*it1);
		if (it != tags.end())
		{
			changed = true;
			tags.erase(it);
		}
	}
	if (!changed)
		return EXIT_SUCCESS;
	return setTags(filename, tags);
}

int meta::delTag(char* filename, TagLib::String tag)
{
	utils::vout("del tag");
	TagLib::StringList tag1;
	tag1.append(tag);
	return delTag(filename, tag1);
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

int meta::list(TagLib::StringList *tags)
{
	return sql::list(tags);
}
