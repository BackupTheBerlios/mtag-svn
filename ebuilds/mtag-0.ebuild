# Copyright 1999-2007 Gentoo Foundation
# Distributed under the terms of the GNU General Public License v2
# $Header: $

inherit eutils

DESCRIPTION="the fast media tag lib"
HOMEPAGE="http://mtag.berlios.de/"
SRC_URI="http://download.berlios.de/mtag/${P}.tar.gz
	http://download2.berlios.de/mtag/${P}.tar.gz
	http://mtag.berlios.de/dl/${P}.tar.gz"

LICENSE="GPL-2"
SLOT="0"
KEYWORDS="~x86 ~amd64"
IUSE=""

DEPEND="dev-util/cmake
	media-libs/taglib"

src_unpack() {
	unpack
	cmake ${S}
}

src_install() {
	[ ! -d "${D}/usr/bin/" ] && mkdir -p ${D}/usr/bin/
	cp ${S}/mtag ${D}/usr/bin/ || die "install failed"
}
