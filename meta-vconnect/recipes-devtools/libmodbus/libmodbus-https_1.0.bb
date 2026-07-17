DESCRIPTION = " a recipe for https libmodbus library"
LICENSE = "LGPL-2.1"
LIC_FILES_CHKSUM = "file://COPYING.LESSER;md5=4fbd65380cdd255951079008b364516c"
SRC_URI[sha256sum] = "f7a9538f23a8786b1ee62a4b75879b5c0e194e728350de1b741ce7d595970f06"
SRC_URI = "https://github.com/stephane/libmodbus/releases/download/v3.1.5/libmodbus-3.1.5.tar.gz"
DEPENDS = "autoconf-native automake-native libtool-native"
S = "${WORKDIR}/libmodbus-3.1.5"
do_configure() {
        ./configure --host=${HOST_SYS} --prefix=/usr
}

do_compile() { 
    make
}

do_install() {
    make DESTDIR=${D} install
}
