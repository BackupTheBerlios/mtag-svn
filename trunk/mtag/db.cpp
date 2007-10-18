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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdlib.h>
#include <tag.h>

using namespace std;

const char* sql_addTag(const char* filename, const char* tag)
{
	string sql("INSERT INTO tags ('filename', 'tag') VALUES ('");
	sql.append(filename);
	sql.append("', '");
	sql.append(tag);
	sql.append("');");
	return sql.c_str();
}
