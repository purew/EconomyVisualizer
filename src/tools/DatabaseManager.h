

#include <QtCore/QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtCore/QFile>

#include "Transaction.h"

class DatabaseManager : public QObject
{
public:
	DatabaseManager(QObject *parent = 0);
	~DatabaseManager();

	bool openDB();
	bool deleteDB();
	QSqlError lastError();

	bool addTransaction( Transaction t );

private:
	QSqlDatabase db;
};
