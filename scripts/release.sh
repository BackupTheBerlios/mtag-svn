#! /bin/bash

[ "x$1" == "x" ] && echo "release?" && exit

RELEASE="$1"
echo making release: ${RELEASE}

(cd trunk/mtag ; make clean)
svn cp trunk/mtag tags/mtag-${RELEASE}
svn --force rm mtag-${RELEASE}/*~
svn --force rm mtag-${RELEASE}/*.mp3
svn --force rm mtag-${RELEASE}/*.ogg
svn --force rm mtag-${RELEASE}/CMakeCache.txt
sed -e 's/-Wall ?//' -e 's/CMAKE_VERBOSE_MAKEFILE ON/CMAKE_VERBOSE_MAKEFILE OFF/' -i mtag-${RELEASE}/CMakeLists.txt

#svn ci -m "release ${RELEASE}"
cp -r tags/mtag-${RELEASE} tars/mtag-${RELEASE}
cd tars/mtag-${RELEASE}
rm -rf .??*
rm -rf *.kdevelop* templates
cd ..
tar -czf mtag-${RELEASE}.tar.gz mtag-${RELEASE}
gpg -b mtag-${RELEASE}.tar.gz
svn add mtag-${RELEASE}.tar.gz*
rm -rf mtag-${RELEASE}

svn cp ebuilds/mtag-base.ebuild ebuilds/mtag-${RELEASE}.ebuild


#svn ci -m "release ${RELEASE}"