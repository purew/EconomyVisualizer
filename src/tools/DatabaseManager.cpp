

#include <QDir>
#include "DatabaseManager.h"


bool DatabaseManager::openDB()
{
	// Find QSLite driver
	db = QSqlDatabase::addDatabase("QSQLITE");


	// NOTE: We have to store database file into user home folder in Linux
	QString path(QDir::home().path());
	path.append(QDir::separator()).append("my.db.sqlite");
	path = QDir::toNativeSeparators(path);
	db.setDatabaseName(path);


	// Open databasee
	return db.open();
}

QSqlError DatabaseManager::lastError()
{
	// If opening database has failed user can ask
	// error description by QSqlError::text()
	return db.lastError();
}

bool DatabaseManager::deleteDB()
{
	// Close database
	db.close();


	// NOTE: We have to store database file into user home folder in Linux
	QString path(QDir::home().path());
	path.append(QDir::separator()).append("my.db.sqlite");
	path = QDir::toNativeSeparators(path);
	return QFile::remove(path);

}
