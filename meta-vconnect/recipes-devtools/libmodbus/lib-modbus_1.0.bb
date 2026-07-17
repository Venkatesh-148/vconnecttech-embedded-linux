DESCRIPTION = "Recipe for libmodbus library"

LICENSE = "LGPL-2.1-or-later"
LIC_FILES_CHKSUM = "file://COPYING.LESSER;md5=6a6a8e020838b23406c81b19c1d46df6"

SRC_URI = "git://github.com/stephane/libmodbus.git;branch=master;protocol=https"
SRCREV = "170b042c374b7315c2074cc871d6d7f75cca9036"

S = "${WORKDIR}/git"
DEPENDS += "autoconf-native automake-native libtool-native"
do_configure() {
    cd ${S}

    ./autogen.sh \
        --prefix=/usr \
        --host=${HOST_SYS}
}

do_compile() {
    cd ${S}

    make
}

do_install() {
    cd ${S}

    make install DESTDIR=${D}
}
