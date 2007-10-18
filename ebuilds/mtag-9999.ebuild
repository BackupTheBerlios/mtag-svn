# Copyright 1999-2007 Gentoo Foundation
# Distributed under the terms of the GNU General Public License v2
# $Header: $

inherit eutils subversion

DESCRIPTION="the fast media tag lib"
HOMEPAGE="http://mtag.berlios.de/"
SRC_URI=""

LICENSE="GPL-2"
SLOT="0"
KEYWORDS="~x86 ~amd64"
IUSE=""

DEPEND="dev-util/cmake
	media-libs/taglib
	dev-util/subversion"

src_unpack() {
        local repo_uri="http://svn.berlios.de/svnroot/repos/mtag"
        subversion_fetch ${repo_uri}/trunk/mtag
		cmake ${S}
}

src_install() {
	[ ! -d "${D}/usr/bin/" ] && mkdir -p ${D}/usr/bin/
	cp ${S}/mtag ${D}/usr/bin/ || die "install failed"
}

