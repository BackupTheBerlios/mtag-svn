# Copyright 1999-2007 Gentoo Foundation
# Distributed under the terms of the GNU General Public License v2
# $Header: $

inherit eutils

DESCRIPTION="the fast media tag lib"
HOMEPAGE="http://mtag.berlios.de/"
SRC_URI="http://svn.berlios.de/svnroot/repos/mtag/tars/${P}.tar.gz
	http://download.berlios.de/mtag/${P}.tar.gz
	http://download2.berlios.de/mtag/${P}.tar.gz"

LICENSE="GPL-2"
SLOT="0"
KEYWORDS="~x86 ~amd64"
IUSE="doc"

DEPEND="dev-util/cmake
	media-libs/taglib
	>=dev-db/sqlite-3.3.12"

RDEPEND="media-libs/taglib
    >=dev-db/sqlite-3.3.12"

src_compile() {
	cd ${S}
	cmake ${S} || die "compile failed!"
	emake || die "compile failed!"
}

src_install() {
	dobin ${S}/mtag
	dodoc ${S}/README ${S}/COPYING
	if use doc; then
		dohtml ${S}/html/*
	fi
}
