
#ifndef TRANSACTION_H_
#define TRANSACTION_H_

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

private:

};


#endif
