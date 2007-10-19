#! /bin/bash

[ "x$1" == "x" ] && echo "release?" && exit

RELEASE="$1"
echo making release: ${RELEASE}

svn up

(cd trunk/mtag ; make clean)
svn cp trunk/mtag tags/mtag-${RELEASE}
svn --force rm tags/mtag-${RELEASE}/*~
svn --force rm tags/mtag-${RELEASE}/*.mp3
svn --force rm tags/mtag-${RELEASE}/*.ogg
svn --force rm tags/mtag-${RELEASE}/*.sq3
svn --force rm tags/mtag-${RELEASE}/*.db
svn --force rm tags/mtag-${RELEASE}/CMakeCache.txt
svn --forec rm tags/mtag-${RELEASE}/CMakeFiles
svn --forec rm tags/mtag-${RELEASE}/Makefile
svn --forec rm tags/mtag-${RELEASE}/cmake_install.cmake

sed -e 's/-Wall ?//' -e 's/CMAKE_VERBOSE_MAKEFILE ON/CMAKE_VERBOSE_MAKEFILE OFF/' -i tags/mtag-${RELEASE}/CMakeLists.txt

svn export tags/mtag-${RELEASE} tars/mtag-${RELEASE}

rm -rf tars/mtag-${RELEASE}/.??*
rm -rf tars/mtag-${RELEASE}/*.kdevelop*
rm -rf tars/mtag-${RELEASE}/templates
#find tars/mtag-${RELEASE}/ -name .svn -exec rm -rf {} \;

cd tars
tar -czf mtag-${RELEASE}.tar.gz mtag-${RELEASE}
gpg -b mtag-${RELEASE}.tar.gz
svn add mtag-${RELEASE}.tar.gz*
#scp mtag-${RELEASE}.tar.gz* shell.berlios.de:/home/groups/mtag/htdocs/dl/
rm -rf mtag-${RELEASE}
cd ..

svn cp ebuilds/mtag-base.ebuild ebuilds/mtag-${RELEASE}.ebuild

svn ci -m "release ${RELEASE}"
