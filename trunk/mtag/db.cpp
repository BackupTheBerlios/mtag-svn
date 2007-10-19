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

using namespace std;

int sql_openDB(sqlite3 **db)
{
	if(sqlite3_open("mtag.db", db) != SQLITE_OK)
		return EXIT_FAILURE;
	return EXIT_SUCCESS;
}

int sql_closeDB(sqlite3* db)
{
	return sqlite3_close(db);
}

int sql_addTag(const char* filename, const char* tag, sqlite3* db)
{
	string sql("INSERT INTO tags(filename, tag) VALUES('");
	sql.append(filename);
	sql.append("', '");
	sql.append(tag);
	sql.append("');");
	return sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);
}

int sql_addTag(const char* filename, const char* tag)
{
	sqlite3* db;
	if(sql_openDB(&db) != EXIT_SUCCESS)
		return EXIT_FAILURE;
	int res = sql_addTag(filename, tag, db);
	sql_closeDB(db);
	return res;

}

int sql_clearTags(const char* filename, sqlite3* db)
{
	string sql("DELETE FROM tags WHERE filename='");
	sql.append(filename);
	sql.append("';");
	return sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);
}

int sql_clearTags(const char* filename)
{
	sqlite3* db;
	if(sql_openDB(&db) != EXIT_SUCCESS)
		return EXIT_FAILURE;
	int res = sql_clearTags(filename, db);
	sql_closeDB(db);
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

int sql_search(const char* tag, TagLib::StringList *files, sqlite3* db){
	string sql("SELECT DISTINCT filename FROM tags WHERE tag='");
	sql += tag;
	sql += "';";
	sqlite3_exec(db, sql.c_str(), search_callback, files, NULL);
}

int sql_search(const char* tag, TagLib::StringList *files)
{
	sqlite3* db;
	if(sql_openDB(&db) != EXIT_SUCCESS)
		return EXIT_FAILURE;
	int res = sql_search(tag, files, db);
	sql_closeDB(db);
	return res;
}
