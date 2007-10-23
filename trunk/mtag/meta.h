//
// C++ Interface: meta
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

/* For taglib */
#include <fileref.h>
#include <tag.h>
#include <tstringlist.h>

/* For sqlite3 */
#include <sqlite3.h>

using namespace std;

/**
 * metahandling of data.
 * bundles database and filehandling.
 */
class meta
{
	private:
		/**
		 * @see meta::syncdir(const char *dirname)
		 */
		static int syncdir(const char *dirname, sqlite3 *db);
	public:
		/**
		 * get tags from file
		 * @param [in] filename target file
		 * @param [out] tags taglist of file
		 */
		static int getTags(char* filename, TagLib::StringList *tags);
		
		/**
		 * set tags to file
		 * @param [in] filename target file
		 * @param [in] tags taglist to set
		 */
		static int setTags(char* filename, TagLib::StringList tags);
		
		/**
		 * clear tags from file
		 * @param [in] filename target file
		 */
		static int clearTags(char* filename);

		/**
		 * add tag to file
		 * @param [in] filename target file
		 * @param [in] tag tag to add
		 */
		static int addTag(char* filename, TagLib::String tag);
		
		/**
		 * remove tag from file
		 * @param [in] filename target file
		 * @param [in] tag tag to remove
		 */static int delTag(char* filename, TagLib::String tag);
		
		/**
		 * sync dir with database.
		 * @param [in] dirname path to direcoy
		 */
		static int syncdir(const char *dirname);
		
		/**
		 * search for a tag
		 * @param [in] tag tag to look for
		 * @param [out] files list of files tagged with tag
		 * @see sql::search
		 */
		static int search(const char *tag, TagLib::StringList *files);
		
		/**
		 * list all tags.
		 * @param [out] tags list of tags
		 * @see sql::list
		 */
		static int list(TagLib::StringList *tags);
};
