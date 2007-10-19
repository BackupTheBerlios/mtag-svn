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
#include "tagger.h"
#include "db.h"

/* For taglib */
#include <fileref.h>
#include <tag.h>
#include <tstringlist.h>

/* For sqlite3 */
#include <sqlite3.h>

/* For fs */
#include <sys/types.h>
#include <dirent.h>

using namespace std;

int meta_getTags(char* filename, TagLib::StringList *tags)
{
	return getTags(filename, tags);
}

int meta_setTags(char* filename, TagLib::StringList tags)
{
	sqlite3 *db;
	if (sql::sql_openDB(&db) != EXIT_SUCCESS)
		return setTags(filename, tags);
	sql_clearTags(filename, db);
	for (TagLib::StringList::Iterator it = tags.begin(); it != tags.end(); it++)
		sql_addTag(filename, (*it).toCString(), db);
	sql_closeDB(db);
	return setTags(filename, tags);
}

int meta_clearTags(char* filename)
{
	if (meta_getTags(filename, NULL) == EXIT_SUCCESS)
	{
		sql_clearTags(filename);
		return clearTags(filename);
	}
	return EXIT_FAILURE;
}

int meta_addTag(char* filename, TagLib::String tag)
{
	TagLib::StringList tags;
	if (meta_getTags(filename, &tags) != EXIT_SUCCESS)
		return EXIT_FAILURE;
	if (tags.find(tag) == tags.end())
		tags.append(tag);
	return meta_setTags(filename, tags);
}

int meta_delTag(char* filename, TagLib::String tag)
{
	TagLib::StringList tags;
	if (meta_getTags(filename, &tags) != EXIT_SUCCESS)
		return EXIT_FAILURE;
	TagLib::StringList::Iterator it = tags.find(tag);
	if (it != tags.end())
		tags.erase(it);
	return meta_setTags(filename, tags);
}

int meta_syncdir(const char *dirname, sqlite3* db)
{
	DIR *dir;
	struct dirent *entry;
	if (!(dir = opendir(dirname))) {
		TagLib::StringList tags;
		if (getTags(dirname, &tags) == EXIT_SUCCESS)
		{
			if (!tags.isEmpty())
			{
				cout << dirname << ": " << tags << endl;
				sql_clearTags(dirname, db);
				for (TagLib::StringList::Iterator it = tags.begin(); it != tags.end(); it++)
				{
					sql_addTag(dirname, (*it).toCString(), db);
				}
			}
			return EXIT_SUCCESS;
		}
		return EXIT_FAILURE;
	}

	string sdirname(dirname);
	while (entry=readdir(dir)) {
		string s(entry->d_name);
		if (s != string(".") && s != string(".."))
		{
			meta_syncdir((sdirname + "/" + entry->d_name).c_str(), db);
		}
	}
	closedir(dir);
	return EXIT_SUCCESS;
}


int meta_syncdir(const char *dirname)
{
	sqlite3* db;
	if(sql_openDB(&db) != EXIT_SUCCESS)
	{
		cerr << "databaseerror" << endl;
		return EXIT_FAILURE;
	}
	int res = meta_syncdir(dirname, db);
	sql_closeDB(db);
	return res;
}



int meta_search(char *tag, TagLib::StringList *files)
{
	return sql_search(tag, files);
}
