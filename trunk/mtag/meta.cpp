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
	return setTags(filename, tags);
}

int meta_clearTags(char* filename)
{
	if (meta_getTags(filename, NULL) == EXIT_SUCCESS)
		return clearTags(filename);
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
				for (TagLib::StringList::Iterator it = tags.begin(); it != tags.end(); it++)
				{
					const char *sql =  sql_addTag(dirname, (*it).toCString());
					cout << sql << endl;
					char **errormsg;
					sqlite3_exec(db, sql, NULL, NULL, errormsg);
					cout << *errormsg << endl;
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
	if(sqlite3_open("mtag.db", &db) != SQLITE_OK)
	{
		cerr << "databaseerror" << endl;
		return EXIT_FAILURE;
	}
	
	int res = meta_syncdir(dirname, db);

	sqlite3_close(db);
	return res;
}

int search_callback(void *filesp, int argc, char **argv, char **colnames)
{
	TagLib::StringList *files = (TagLib::StringList *) filesp;
	for (int i = 0; i < argc; i++)
	{
		files->append(argv[i]);
	}
	return EXIT_SUCCESS;
}

int meta_search(char *tag, TagLib::StringList *files)
{
	sqlite3* db;
	if(sqlite3_open("mtag.db", &db) != SQLITE_OK)
	{
		cerr << "databaseerror" << endl;
		return EXIT_FAILURE;
	}
	string sql("SELECT filename FROM tags WHERE tag='");
	sql += tag;
	sql += "';";
	sqlite3_exec(db, sql.c_str(), search_callback, files, NULL);
	sqlite3_close(db);
	return EXIT_SUCCESS;
}
