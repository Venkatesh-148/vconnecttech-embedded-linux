DESCRIPTION="recipe for hello c"
LICENSE="CLOSED"

SRC_URI="file://hello.c \
         file://world.cpp \
"

S="${WORKDIR}"

do_compile(){
   cd ${S}
   ${CC} hello.c -o hello
   ${CXX} world.cpp -o world
}
do_install(){
   install -d ${D}${bindir}
   install -m 777 ${S}/hello ${D}${bindir}
   install -m 777 ${S}/world ${D}${bindir}
}

PACKAGES_${PN} ="hello-c hello-cpp"

FILES_hello-c ="/usr/bin/hello"
FILES_hello-cpp ="/usr/bin/world"
