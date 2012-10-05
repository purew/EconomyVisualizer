

#include <QStringList>
#include <QPushButton>

#include "DataImport.h"




std::list<Transaction> SplitterDialog::splitIntoTransactions(QString str)
{
	std::list<Transaction> transactionList;

	QStringList lines = str.split("\n", QString::SkipEmptyParts);

	tableWidget->setRowCount(5);

	int row=0;
	QStringList::iterator line = lines.begin();
	for (;line != lines.end(); ++line)
	{

		QStringList components = (*line).split("\t",QString::SkipEmptyParts);
		if (tableWidget->columnCount() == 0)
			tableWidget->setColumnCount(components.size());

		int col=0;
		QStringList::iterator part = components.begin();
		for (;part != components.end(); ++part)
		{
			QTableWidgetItem *newItem = new QTableWidgetItem(*part);
			tableWidget->setItem(row,col, newItem);
			col++;
		}
		row++;
		//Transaction t;
		//t.transactionDate = QDateTime::fromString(components[0], "yy-mm-dd");

	}

	tableWidget->resize(1,1);
	int w = tableWidget->columnWidth(0)*tableWidget->columnCount()+20;
	int h = tableWidget->rowHeight(0)*tableWidget->rowCount()+27;
	tableWidget->setMaximumSize(QSize(w,h));
	tableWidget->setMinimumSize(tableWidget->maximumSize());

	show();
	raise();
	activateWindow();

	return transactionList;
}

SplitterDialog::SplitterDialog(QWidget *parent)
	: QDialog(parent)
{

	tableWidget = new QTableWidget(this);
	btOk = new QPushButton(tr("&Ok"));

	btCancel = new QPushButton(tr("&Cancel"));
	QObject::connect(btCancel,SIGNAL(clicked()), this, SLOT(reject()));

	hlayout = new QHBoxLayout();
	hlayout->addWidget(btOk);
	hlayout->addWidget(btCancel);

	vlayout = new QVBoxLayout();
	vlayout->addWidget(tableWidget);
	vlayout->addLayout(hlayout);



	setLayout(vlayout);
}

SplitterDialog::~SplitterDialog()
{
	/*delete tableWidget;
	delete btOk;
	delete btCancel;*/
};
