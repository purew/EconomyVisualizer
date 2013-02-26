

#include <QtCore/QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtCore/QFile>

class DatabaseManager : public QObject
{
public:
	DatabaseManager(QObject *parent = 0);
	~DatabaseManager();

	bool openDB();
	bool deleteDB();
	QSqlError lastError();

private:
	QSqlDatabase db;
};
