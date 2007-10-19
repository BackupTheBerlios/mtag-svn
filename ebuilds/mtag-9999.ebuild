# Copyright 1999-2007 Gentoo Foundation
# Distributed under the terms of the GNU General Public License v2
# $Header: $

inherit eutils subversion

DESCRIPTION="the fast media tag lib"
HOMEPAGE="http://mtag.berlios.de/"
SRC_URI=""
ESVN_REPO_URI="http://svn.berlios.de/svnroot/repos/mtag/trunk/mtag"

LICENSE="GPL-2"
SLOT="0"
KEYWORDS="~x86 ~amd64"
IUSE="doc"

DEPEND="dev-util/cmake
	media-libs/taglib
	dev-util/subversion
	>=dev-db/sqlite-3.3.12
	doc? ( app-doc/doxygen )"

src_compile() {
	cd ${S}
	cmake ${S}
	make
	if use doc; then
		doxygen ${S}
	fi
}

src_install() {
	mkdir -p ${D}/usr/share/doc/${P}/
	dobin ${S}/mtag
	dodoc ${S}/README ${S}/COPYING
	if use doc; then
		cp -r ${S}/html ${D}/usr/share/doc/${P}/
	fi
}
