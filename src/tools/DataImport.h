
#ifndef DATAIMPORT_H_
#define DATAIMPORT_H_

#include <list>
#include <vector>
#include <iostream>

#include <QtCore/QString>
#include <QtCore/QDateTime>
#include <QtGui/QDialog>
#include <QtGui/QWidget>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QLayout>
#include <QtGui/QComboBox>
#include <QTableView>
#include <QStandardItem>
#include <QMenu>
#include <QAction>

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

	Transaction createTransaction( QStringList components );
	bool eventFilter(QObject *, QEvent *);

	QTableView *transactionTable;
    QStandardItemModel *myTableModel;

    std::vector<Transaction> transactions;

    // GUI
	std::vector<QPlainTextEdit*> textColumns;
	std::vector<QVBoxLayout*> columnLayouts;
	std::vector<QComboBox*> columnComboBox;

	QPushButton *btOk;
	QPushButton *btCancel;

	QHBoxLayout *hlayoutUpper;
	QHBoxLayout *hlayoutLower;
	QVBoxLayout *vlayout;
	QStringList columnTypes;

public slots:
	void formatUserData();

	void setCategoryOfTransactionRow(QObject* args);

};



/** Dialog window responsible for helping user classify transactions */
class ClassifyDialog : public QDialog
{
	Q_OBJECT

public:

	ClassifyDialog( QWidget * parent = 0 ) {};
	~ClassifyDialog() {};

	void setTextDate( const QString text) {textDate = text;};
	void setTextDescription( const QString text ) {textDescription = text;};
	void setTextAmount( const QString text ) {textAmount = text;};

private:

	QString textDate;
	QString textDescription;
	QString textAmount;

public slots:

	int exec();

};

class SplitterWndwMenuArgs : public QObject
{
public:
	SplitterWndwMenuArgs(int  row,int category, QObject *parent=0);
	~SplitterWndwMenuArgs() {;};
	int row, category;
};

#endif
