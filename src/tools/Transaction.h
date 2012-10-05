
#ifndef TRANSACTION_H_
#define TRANSACTION_H_

#include <QDateTime>


class Transaction
{
public:

	QDateTime transactionDate;
	QString description;
	float amount;
	float balance;

private:

};


#endif
