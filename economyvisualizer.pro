
TEMPLATE = app
TARGET = economyvisualizer
DEPENDPATH += . src
INCLUDEPATH += .

# Input
CONFIG += qt debug
 
HEADERS += src/MainWindow.h \
			src/tools/DataImport.h \
			src/tools/Transaction.h
SOURCES += src/economyvisualizer.cpp \
			src/MainWindow.cpp \
			src/tools/DataImport.cpp \
			src/tools/Transaction.cpp

CONFIG(debug, debug|release) {
	DESTDIR = Debug
	OBJECTS_DIR =  $${DESTDIR}/obj
	MOC_DIR =  $${DESTDIR}/moc
	RCC_DIR =  $${DESTDIR}/rcc
	UI_DIR =  $${DESTDIR}/ui
} else	{	
	DESTDIR = Release
	OBJECTS_DIR =  $${DESTDIR}/obj
	MOC_DIR =  $${DESTDIR}/moc
	RCC_DIR =  $${DESTDIR}/rcc
	UI_DIR = Release/ui
}

