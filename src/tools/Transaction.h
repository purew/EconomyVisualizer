
#ifndef TRANSACTION_H_
#define TRANSACTION_H_

#include <QString>
#include <QDateTime>


const int indexTransactionDate = 1;
const int indexTransactionDescription = 2;
const int indexTransactionAmount = 3;



class Transaction
{
public:

	QDateTime transactionDate;
	QString description;
	float amount;
	float balance;
	int primaryCategory;
	int secondaryCategory;

	QString toQString() {return QString(transactionDate.toString(QString("yy-MM-dd")));}
private:

};


#endif
