#############################################################################
# Makefile for building: bloom_lab
# Generated by qmake (2.01a) (Qt 4.6.3) on: Tue Dec 6 16:59:59 2011
# Project:  bloom_lab.pro
# Template: app
# Command: /usr/bin/qmake-qt4 -spec /usr/share/qt4/mkspecs/linux-g++ -unix CONFIG+=debug -o Makefile bloom_lab.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_OPENGL_LIB -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -pipe -g -Wall -W -D_REENTRANT $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4/QtOpenGL -I/usr/include/qt4 -Ilab -Ilib -Imath -Isupport -I/usr/X11R6/include -I. -I.
LINK          = g++
LFLAGS        = 
LIBS          = $(SUBLIBS)  -L/usr/lib -L/usr/X11R6/lib -lQtOpenGL -lQtGui -lQtCore -lGLU -lGL -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake-qt4
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = lab/glwidget.cpp \
		lib/targa.cpp \
		lib/glm.cpp \
		support/resourceloader.cpp \
		support/mainwindow.cpp \
		support/main.cpp \
		support/camera.cpp moc_glwidget.cpp \
		moc_mainwindow.cpp
OBJECTS       = glwidget.o \
		targa.o \
		glm.o \
		resourceloader.o \
		mainwindow.o \
		main.o \
		camera.o \
		moc_glwidget.o \
		moc_mainwindow.o
DIST          = /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/opengl.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		bloom_lab.pro
QMAKE_TARGET  = bloom_lab
DESTDIR       = 
TARGET        = bloom_lab

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET): ui_mainwindow.h $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: bloom_lab.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/debug.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/opengl.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/libQtOpenGL.prl \
		/usr/lib/libQtGui.prl \
		/usr/lib/libQtCore.prl
	$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++ -unix CONFIG+=debug -o Makefile bloom_lab.pro
/usr/share/qt4/mkspecs/common/g++.conf:
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/debug.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/opengl.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/libQtOpenGL.prl:
/usr/lib/libQtGui.prl:
/usr/lib/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++ -unix CONFIG+=debug -o Makefile bloom_lab.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/bloom_lab1.0.0 || $(MKDIR) .tmp/bloom_lab1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/bloom_lab1.0.0/ && $(COPY_FILE) --parents lab/glwidget.h lib/targa.h lib/glm.h math/vector.h support/resourceloader.h support/mainwindow.h support/camera.h lib/targa.h .tmp/bloom_lab1.0.0/ && $(COPY_FILE) --parents lab/glwidget.cpp lib/targa.cpp lib/glm.cpp support/resourceloader.cpp support/mainwindow.cpp support/main.cpp support/camera.cpp .tmp/bloom_lab1.0.0/ && $(COPY_FILE) --parents support/mainwindow.ui support/mainwindow.ui .tmp/bloom_lab1.0.0/ && (cd `dirname .tmp/bloom_lab1.0.0` && $(TAR) bloom_lab1.0.0.tar bloom_lab1.0.0 && $(COMPRESS) bloom_lab1.0.0.tar) && $(MOVE) `dirname .tmp/bloom_lab1.0.0`/bloom_lab1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/bloom_lab1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_glwidget.cpp moc_mainwindow.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_glwidget.cpp moc_mainwindow.cpp
moc_glwidget.cpp: support/camera.h \
		math/vector.h \
		support/resourceloader.h \
		lib/glm.h \
		lab/glwidget.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) lab/glwidget.h -o moc_glwidget.cpp

moc_mainwindow.cpp: support/mainwindow.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) support/mainwindow.h -o moc_mainwindow.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all: ui_mainwindow.h ui_mainwindow.h
compiler_uic_clean:
	-$(DEL_FILE) ui_mainwindow.h ui_mainwindow.h
ui_mainwindow.h: support/mainwindow.ui \
		lab/glwidget.h \
		support/camera.h \
		math/vector.h \
		support/resourceloader.h \
		lib/glm.h
	/usr/bin/uic-qt4 support/mainwindow.ui -o ui_mainwindow.h

ui_mainwindow.h: support/mainwindow.ui \
		lab/glwidget.h \
		support/camera.h \
		math/vector.h \
		support/resourceloader.h \
		lib/glm.h
	/usr/bin/uic-qt4 support/mainwindow.ui -o ui_mainwindow.h

compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_uic_clean 

####### Compile

glwidget.o: lab/glwidget.cpp lab/glwidget.h \
		support/camera.h \
		math/vector.h \
		support/resourceloader.h \
		lib/glm.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o glwidget.o lab/glwidget.cpp

targa.o: lib/targa.cpp lib/targa.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o targa.o lib/targa.cpp

glm.o: lib/glm.cpp lib/glm.h \
		lib/targa.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o glm.o lib/glm.cpp

resourceloader.o: support/resourceloader.cpp support/resourceloader.h \
		lib/glm.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o resourceloader.o support/resourceloader.cpp

mainwindow.o: support/mainwindow.cpp support/mainwindow.h \
		ui_mainwindow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o mainwindow.o support/mainwindow.cpp

main.o: support/main.cpp support/mainwindow.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o support/main.cpp

camera.o: support/camera.cpp support/camera.h \
		math/vector.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o camera.o support/camera.cpp

moc_glwidget.o: moc_glwidget.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_glwidget.o moc_glwidget.cpp

moc_mainwindow.o: moc_mainwindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_mainwindow.o moc_mainwindow.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

