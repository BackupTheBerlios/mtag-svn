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
 * handles sql things.
 **/
class sql
{
	private:
		static const char *database;
	public:
		
		/**
		 * set database file
		 * @param filename path to databse file
		 */
		static void setDataBase(const char *filename);
		
		/**
		* open the database.
		* @param db database handle
		*/
		static int openDB(sqlite3 **db);
		
		/**
		* close the database.
		* @param [in] db database handle
		*/
		static int closeDB(sqlite3 *db);
	
		/**
		* add tag to file.
		* @param [in] filename target file
		* @param [in] tag tag to add
		*/
		static int addTag(const char* filename, const char* tag);
		/**
		* @see sql::addTag
		*/
		static int addTag(const char* filename, const char* tag, sqlite3* db);
		
		/**
		* clear tags of file.
		* @param [in] filename target file
		*/
		static int clearTags(const char* filename);
		/**
		* @see sql::clearTags
		*/
		static int clearTags(const char* filename, sqlite3* db);
	
		/**
		* search for files with certain tag.
		* @param [in] tag tag to search for
		* @param [out] files list of files tagged with tag
		*/
		static int search(const char* tag, TagLib::StringList *files);
		/**
		* @see search
		*/
		static int search(const char* tag, TagLib::StringList *files, sqlite3* db);
		
		/**
		 * wipe all tags from files with filname like path%
		 * @param [in] path path to wipe
		 */
		static int wipePath(const char* path);
		
		/**
		 * @see wipePath
		 */
		static int wipePath(const char* path, sqlite3* db);
};
