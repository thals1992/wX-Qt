#!/usr/bin/env python3
#
# generate wxqt.pro
#

from typing import List
import glob

cppFiles: List[str] = glob.glob("src/*.cpp") + glob.glob("src/*/*.c*")
headerFiles: List[str] = glob.glob("src/*/*.h")

targetFile: str = "wxqt.pro"
header: str = """QT += core gui network widgets
CONFIG += c++17
DEFINES += QT_DEPRECATED_WARNINGS
INCLUDEPATH += src

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG(debug, debug|release) {
    DESTDIR = build/debug
}
CONFIG(release, debug|release) {
    DESTDIR = build/release
}

OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.qrc
UI_DIR = $$DESTDIR/.u

SOURCES += \\
"""

footer: str = """
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
"""

fh = open(targetFile, "w")
fh.write(header)
for cpp in sorted(cppFiles):
    fh.write(" " * 4 + cpp + " \\" + '\n')

fh.write("\nHEADERS += \\" + "\n")
for f in sorted(headerFiles):
    fh.write(" " * 4 + f + " \\" + '\n')

# RESOURCES = resourceCreation/res.qrc resourceCreation/images.qrc
qrcFiles: List[str] = glob.glob("resourceCreation/*.qrc")
fh.write("\nRESOURCES += \\" + "\n")
for qrc in sorted(qrcFiles):
    fh.write(" " * 4 + qrc + " \\" + '\n')

fh.write(footer)
fh.close()
