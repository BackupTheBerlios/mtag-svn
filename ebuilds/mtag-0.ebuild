# Copyright 1999-2007 Gentoo Foundation
# Distributed under the terms of the GNU General Public License v2
# $Header: $

inherit eutils

DESCRIPTION="the fast media tag lib"
HOMEPAGE="http://mtag.berlios.de/"
SRC_URI="http://svn.berlios.de/svnroot/repos/${PN}/tars/${P}.tar.gz"

LICENSE="GPL-2"
SLOT="0"
KEYWORDS="~x86 ~amd64"
IUSE=""

DEPEND="dev-util/cmake
	media-libs/taglib"

RDEPEND="media-libs/taglib"

src_unpack() {
	unpack ${A}
	cd ${S}
	cmake ${S}
}

src_install() {
	mkdir -p ${D}/usr/bin/ ${D}/usr/share/doc/${P}/
	dobin ${S}/mtag
	dodoc ${S}/README ${S}/COPYING
	if use doc; then
		dohtml ${S}/html/*
	fi
}
