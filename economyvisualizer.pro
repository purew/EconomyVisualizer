
TEMPLATE = app
TARGET = economyvisualizer
DEPENDPATH += . src
INCLUDEPATH += .

# Configuration
CONFIG += qt debug
QT += sql
 
 
HEADERS += src/MainWindow.h \
			src/tools/DataImport.h \
			src/tools/Transaction.h \
			src/tools/DatabaseManager.h
SOURCES += src/economyvisualizer.cpp \
			src/MainWindow.cpp \
			src/tools/DataImport.cpp \
			src/tools/Transaction.cpp \
			src/tools/DatabaseManager.cpp

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

