#! /bin/bash

[ "x$1" == "x" ] && echo "release?" && exit

RELEASE="$1"
echo making release: ${RELEASE}

# make sure everything is clean
svn up
(cd trunk/mtag ; make clean)
(cd trunk/mtag ; doxygen)

# append release to changelog
echo "$(date +%Y/%m/%d)	mtag-${RELEASE} released" > changlog.tmp
cat trunk/mtag/ChangeLog | sed "s:$(date +%Y/%m/%d):\t:" >> changlog.tmp
mv changlog.tmp trunk/mtag/ChangeLog

# copy trunk to tag, clean it
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

# change some things to for the release
sed -e 's/-Wall//' -e 's/CMAKE_VERBOSE_MAKEFILE ON/CMAKE_VERBOSE_MAKEFILE OFF/' -i tags/mtag-${RELEASE}/CMakeLists.txt
sed -e "s/#define VERSION .*/#define VERSION \"v${RELEASE}\"/" -i tags/mtag-${RELEASE}/config.h
sed -e "s/PROJECT_NUMBER.*/PROJECT_NUMBER = \"v${RELEASE}\"/" -i tags/mtag-${RELEASE}/Doxyfile

# run doxygen to get fresh docs
(cd tags/mtag-${RELEASE} ; doxygen)
svn --force rm tags/mtag-${RELEASE}/xml
svn --force rm tags/mtag-${RELEASE}/latex
svn --force rm tags/mtag-${RELEASE}/*.tag

# export svn tag to tar it
svn export tags/mtag-${RELEASE} tars/mtag-${RELEASE}
rm -rf tars/mtag-${RELEASE}/.??*
rm -rf tars/mtag-${RELEASE}/*.kdevelop*
rm -rf tars/mtag-${RELEASE}/templates

# make tarball from release
cd tars
tar -czf mtag-${RELEASE}.tar.gz mtag-${RELEASE}
gpg -ab mtag-${RELEASE}.tar.gz ## sign it with your key
svn add mtag-${RELEASE}.tar.gz*
rm -rf mtag-${RELEASE}
md5sum * > MD5SUM
cd ..

## copy ebuild from basic ebuild
svn cp ebuilds/mtag-0_pre0.ebuild ebuilds/mtag-${RELEASE}.ebuild

## check release in
echo "\$ svn st"
svn st
echo ""
echo "shure you want this checked in?"
read a
svn ci -m "release ${RELEASE}"
