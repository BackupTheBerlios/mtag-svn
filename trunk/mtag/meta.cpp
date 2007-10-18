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

/* For taglib */
#include <fileref.h>
#include <tag.h>
#include <tstringlist.h>

/* For sqlite3 */
#include <sqlite3.h>

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
	tags.append(optarg);
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


int meta_syncdir(char *dirname)
{
	// TODO
	return EXIT_FAILURE;
}

int meta_search(char *tag, TagLib::StringList *files)
{
	sqlite3* db;
	if(sqlite3_open("mtag.db", &db) != SQLITE_OK)
	{
		cerr << "databaseerror" << endl;
		return EXIT_FAILURE;
	}
	string sql("SELECT * FROM tags WHERE tag=");
	sql += tag;
	sql += ";";
	sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);

	files->append("test.xxx");
	sqlite3_close(db);
	return EXIT_SUCCESS;
}
