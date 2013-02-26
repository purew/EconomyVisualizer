
#ifndef DATAIMPORT_H_
#define DATAIMPORT_H_

#include <list>
#include <vector>
#include <QString>
#include <QDateTime>
#include <QDialog>
#include <QWidget>
#include <QPlainTextEdit>
#include <QLayout>
#include <QComboBox>

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

#endif
