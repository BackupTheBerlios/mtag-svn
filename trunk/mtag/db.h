//
// C++ Interface: db
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

/* For sqlite3 */
#include <sqlite3.h>

using namespace std;

/**
 * opens the sqlite3 database.
 */
class sql
{
public:
static int sql_openDB(sqlite3 **db);
static int sql_closeDB(sqlite3 *db);

static int sql_addTag(const char* filename, const char* tag);
static int sql_addTag(const char* filename, const char* tag, sqlite3* db);

static int sql_clearTags(const char* filename);
static int sql_clearTags(const char* filename, sqlite3* db);

static int sql_search(const char* tag, TagLib::StringList *files);
static int sql_search(const char* tag, TagLib::StringList *files, sqlite3* db);
}
