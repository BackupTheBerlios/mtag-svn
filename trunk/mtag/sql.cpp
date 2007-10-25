//
// C++ Implementation: db
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
#include <tag.h>

/* For sqlite3 */
#include <sqlite3.h>


/* For taglib */
#include <fileref.h>

#include "utils.h"

#include "sql.h"

using namespace std;

int search_callback_listappend(void *listp, int argc, char **argv, char **colnames)
{
	TagLib::StringList *list = (TagLib::StringList *)listp;
	for (int i = 0; i < argc; i++)
	{
		list->append(argv[i]);
	}
	return EXIT_SUCCESS;
}

bool sql::created = false;

int sql::openDB(sqlite3 **db)
{
	if(sqlite3_open(database, db) != SQLITE_OK)
	{
		return EXIT_FAILURE;
	}
	if (!created)
	{
		sqlite3_exec(*db, "CREATE TABLE tags (filename TEXT, tag TEXT);", NULL, NULL, NULL);
		utils::vout("CREATE TABLE tags (filename TEXT, tag TEXT);");
		sqlite3_exec(*db, "CREATE INDEX tagsByFile ON tags(filename ASC);", NULL, NULL, NULL);
		utils::vout("CREATE INDEX tagsByFile ON tags(filename ASC);");
		sqlite3_exec(*db, "CREATE INDEX tagsByTags ON tags(tag ASC);", NULL, NULL, NULL);
		utils::vout("CREATE INDEX tagsByTags ON tags(tag ASC);");
		created = true;
	}
	return EXIT_SUCCESS;
}

int sql::closeDB(sqlite3* db)
{
	return sqlite3_close(db);
}

int sql::addTag(const char* filename, const char* tag, sqlite3* db)
{
	string s("INSERT INTO tags(filename, tag) VALUES('");
	s.append(filename);
	s.append("', '");
	s.append(tag);
	s.append("');");
	return sqlite3_exec(db, s.c_str(), NULL, NULL, NULL);
}

int sql::addTag(const char* filename, const char* tag)
{
	sqlite3* db;
	if(openDB(&db) != EXIT_SUCCESS)
		return EXIT_FAILURE;
	int res = addTag(filename, tag, db);
	closeDB(db);
	return res;
}

int sql::clearTags(const char* filename, sqlite3* db)
{
	string s("DELETE FROM tags WHERE filename='");
	s.append(filename);
	s.append("';");
	return sqlite3_exec(db, s.c_str(), NULL, NULL, NULL);
}

int sql::clearTags(const char* filename)
{
	sqlite3* db;
	if(openDB(&db) != EXIT_SUCCESS)
		return EXIT_FAILURE;
	int res = clearTags(filename, db);
	closeDB(db);
	return res;
}


int sql::search(const char* tag, TagLib::StringList *files, sqlite3* db)
{
	string s("SELECT DISTINCT filename FROM tags WHERE tag='");
	s += tag;
	s += "' ORDER BY filename ASC;";
	return sqlite3_exec(db, s.c_str(), search_callback_listappend, files, NULL);
}

int sql::search(const char* tag, TagLib::StringList *files)
{
	sqlite3* db;
	if(openDB(&db) != EXIT_SUCCESS)
		return EXIT_FAILURE;
	int res = search(tag, files, db);
	closeDB(db);
	return res;
}

const char *sql::database;

void sql::setDataBase(const char *filename)
{
	database = filename;
}

int sql::wipePath(const char* path, sqlite3* db)
{
	string s("DELETE FROM tags WHERE filename like '");
	s += path;
	s += "%';";
	return sqlite3_exec(db, s.c_str(), NULL, NULL, NULL);
}

int sql::wipePath(const char* path)
{
	sqlite3* db;
	if(openDB(&db) != EXIT_SUCCESS)
		return EXIT_FAILURE;
	int res = wipePath(path, db);
	closeDB(db);
	return res;
}

int sql::list(TagLib::StringList *tags, sqlite3* db)
{
	string s("SELECT DISTINCT tag FROM tags ORDER BY filename ASC;");
	return sqlite3_exec(db, s.c_str(), search_callback_listappend, tags, NULL);
}

int sql::list(TagLib::StringList *tags)
{
	sqlite3* db;
	if(openDB(&db) != EXIT_SUCCESS)
		return EXIT_FAILURE;
	int res = list(tags, db);
	closeDB(db);
	return res;
}
