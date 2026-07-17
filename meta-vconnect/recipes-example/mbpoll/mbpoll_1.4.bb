DESCRIPTION="recipe for mbpoll"
LICENSE="GPLv3"
LIC_FILES_CHKSUM="file://COPYING;md5=1ebbd3e34237af26da5dc08a4e440464"
SRC_URI="git://github.com/epsilonrt/mbpoll.git;protocol=https;nobranch=1"
SRCREV="81af8ba119d50e63a6c2c2a5eb51a24c97f83a07"
S="${WORKDIR}/git"
DEPENDS ="libmodbus"

inherit cmake pkgconfig
