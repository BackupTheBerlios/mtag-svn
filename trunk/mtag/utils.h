//
// C++ Interface: utils
//
// Description: 
//
//
// Author:  Felix Bechstein <f@ub0r.de>, (C) 2007
//
// Copyright: See COPYING file that comes with this distribution
//
//

#include <stdlib.h>
#include <string>

using namespace std;

/**
 * some usefull things..
 */
class utils
{
	private:
		static string strippath;
	public:
		/**
		 * build an absolut path from path)
		 * @param [in] path path
		 */
		static string absPath(const char* path);
		
		/**
		 * sets path to strip from output.
		 * @param [in] path path
		 */
		static void setStripPath(const char* path);
		
		/**
		 * strips leading path from given path
		 * @param [in] path path
		 * @see setStripPath
		 */
		static string stripPath(const char* path);
};
