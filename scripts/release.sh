#! /bin/bash

[ "x$1" == "x" ] && echo "release?" && exit

RELEASE="$1"
echo making release: ${RELEASE}

svn up

(cd trunk/mtag ; make clean)
(cd trunk/mtag ; doxygen)
echo "$(date +%Y/%m/%d)	mtag-${RELEASE} released" > changlog.tmp
cat trunk/mtag/ChangeLog >> changlog.tmp
mv changlog.tmp trunk/mtag/ChangeLog

svn cp trunk/mtag tags/mtag-${RELEASE}
svn --force rm tags/mtag-${RELEASE}/*~
svn --force rm tags/mtag-${RELEASE}/*.mp3
svn --force rm tags/mtag-${RELEASE}/*.ogg
svn --force rm tags/mtag-${RELEASE}/*.sq3
svn --force rm tags/mtag-${RELEASE}/*.db
svn --force rm tags/mtag-${RELEASE}/CMakeCache.txt
svn --force rm tags/mtag-${RELEASE}/CMakeFiles
svn --force rm tags/mtag-${RELEASE}/Makefile
svn --force rm tags/mtag-${RELEASE}/cmake_install.cmake

sed -e 's/-Wall//' -e 's/CMAKE_VERBOSE_MAKEFILE ON/CMAKE_VERBOSE_MAKEFILE OFF/' -i tags/mtag-${RELEASE}/CMakeLists.txt
sed -e "s/#define VERSION .*/#define VERSION v${RELEASE}/" -i tags/mtag-${RELEASE}/main.cpp
sed -e "s/PROJECT_NUMBER.*/PROJECT_NUMBER = v${RELEASE}/" -i tags/mtag-${RELEASE}/Doxyfile
(cd tags/mtag-${RELEASE} ; doxygen)

svn --force rm tags/mtag-${RELEASE}/xml
svn --force rm tags/mtag-${RELEASE}/latex
svn --force rm tags/mtag-${RELEASE}/*.tag

svn export tags/mtag-${RELEASE} tars/mtag-${RELEASE}

rm -rf tars/mtag-${RELEASE}/.??*
rm -rf tars/mtag-${RELEASE}/*.kdevelop*
rm -rf tars/mtag-${RELEASE}/templates
#find tars/mtag-${RELEASE}/ -name .svn -exec rm -rf {} \;

cd tars
tar -czf mtag-${RELEASE}.tar.gz mtag-${RELEASE}
gpg -ab mtag-${RELEASE}.tar.gz
svn add mtag-${RELEASE}.tar.gz*
#scp mtag-${RELEASE}.tar.gz* shell.berlios.de:/home/groups/mtag/htdocs/dl/
rm -rf mtag-${RELEASE}
md5sum * > MD5SUM
cd ..

svn cp ebuilds/mtag-base.ebuild ebuilds/mtag-${RELEASE}.ebuild

svn ci -m "release ${RELEASE}"
