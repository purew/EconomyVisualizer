

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QFile>

class DatabaseManager : public QObject
{
public:
	DatabaseManager(QObject *parent = 0);
	~DatabaseManager();

public:
	bool openDB();
	bool deleteDB();
	QSqlError lastError();

private:
	QSqlDatabase db;
};
