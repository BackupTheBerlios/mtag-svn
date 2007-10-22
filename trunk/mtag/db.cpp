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

#include "db.h"

using namespace std;

int search_callback(void *filesp, int argc, char **argv, char **colnames)
{
	TagLib::StringList *files = (TagLib::StringList *) filesp;
	for (int i = 0; i < argc; i++)
	{
		files->append(argv[i]);
	}
	return EXIT_SUCCESS;
}


int sql::openDB(sqlite3 **db)
{
	if(sqlite3_open(database, db) != SQLITE_OK)
	{
		return EXIT_FAILURE;
	}
	sqlite3_exec(*db, "CREATE TABLE tags (filename TEXT, tag TEXT);", NULL, NULL, NULL);
	sqlite3_exec(*db, "CREATE INDEX tagsByFile ON tags(filename ASC);", NULL, NULL, NULL);
	sqlite3_exec(*db, "CREATE INDEX tagsByTags ON tags(tag ASC);", NULL, NULL, NULL);
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
	return sqlite3_exec(db, s.c_str(), search_callback, files, NULL);
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