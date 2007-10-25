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
		static bool verbose;
	public:
		/**
		 * sets verbose output.
		 * @param[in] flag
		 */
		static bool setVerbose(const bool flag);
		
		/**
		 * prints out s if verbose
		 * @param [in] s
		 */
		static void vout(const char* s);
		
		/**
		 * @see vout
		 */
		static void vout(const string s);
		
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
