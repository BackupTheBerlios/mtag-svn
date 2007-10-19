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
IUSE="doc"

DEPEND="dev-util/cmake
	media-libs/taglib
	dev-util/subversion
	>=dev-db/sqlite-3.3.12
	doc? app-doc/doxygen"

src() {
        local repo_uri="http://svn.berlios.de/svnroot/repos/mtag"
        subversion_fetch ${repo_uri}/trunk/mtag
		cd ${S}
		cmake ${S}
}

src_unpack() {
	cd ${S}
	cmake ${S}
	if use doc; then
		doxygen ${S}
	fi
}

src_install() {
	[ ! -d "${D}/usr/bin/" ] && mkdir -p ${D}/usr/bin/
	cp ${S}/mtag ${D}/usr/bin/ || die "install failed"
	cp ${S}/README ${S}/COPYING ${D}/usr/share/doc/${P}/
	if use doc; then
		cp -r ${S}/html ${D}/usr/share/doc/${P}/
	fi
}

