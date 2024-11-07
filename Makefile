CC=i686-w64-mingw32-gcc
EDIT=vi
ICON=icon.ico
SRC=main.c
TARGET=ElectronArrangement2
WINDRES=i686-w64-mingw32-windres
edit:
	${EDIT} ${SRC}
compile:
	echo 'MAINICON ICON "${ICON}"'>resource.rc
	${WINDRES} -O coff -o resource.res resource.rc
	${CC} ${SRC} -o ${TARGET}.exe resource.res -static-libgcc -Wall -Wextra
	rm resource.rc resource.res
