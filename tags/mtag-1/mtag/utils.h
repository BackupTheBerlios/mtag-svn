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
	public:
		/**
		 * build an absolut path from path)
		 * @param [in] path path
		 */
		static string absPath(const char* path);
};
