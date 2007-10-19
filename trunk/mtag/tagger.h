//
// C++ Interface: tagger
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

using namespace std;

/**
* handles tagging of files via taglib.
**/
class tagger
{
	public:
	
		/**
		 * get tags of file.
		 * @param [in] filename target file
		 * @param [out] tags list of tags
		 */
		static int getTags(const char* filename, TagLib::StringList *tags);
		
		/**
		 * set tags for file.
		 * @param [in] filename target file
		 * @param [in] tags list of tags
		 */
		static int setTags(const char* filename, TagLib::StringList tags);
		
		/**
		 * clear tags for file.
		 * @param [in] filename target file
		 */
		static int clearTags(const char* filename);
};