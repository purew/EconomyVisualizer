
#ifndef DATAIMPORT_H_
#define DATAIMPORT_H_

#include <list>
#include <QString>
#include <QDateTime>
#include <QDialog>
#include <QWidget>
#include <QTableWidget>
#include <QLayout>

#include "Transaction.h"



/** Dialog window responsible for parsing text as transactions */
class SplitterDialog : public QDialog
{
	Q_OBJECT

public:

	SplitterDialog( QWidget * parent = 0 );
	~SplitterDialog();


	/** Grab a chunk of text and split it into a list of transactions */
	std::list<Transaction> splitIntoTransactions(QString str);

private:

	QTableWidget *tableWidget;

	QPushButton *btOk;
	QPushButton *btCancel;

	QHBoxLayout *hlayout;
	QVBoxLayout *vlayout ;

};

#endif
