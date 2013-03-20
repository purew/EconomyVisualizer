
#include <iostream>


#include <QtCore/QStringList>
#include <QtGui/QPushButton>
#include <QtGui/QMessageBox>
#include <QtGui/QLabel>
#include <QSignalMapper>

#include "DataImport.h"




std::list<Transaction> SplitterDialog::splitIntoTransactions(QString str)
{
	std::list<Transaction> transactionList;

	QStringList lines = str.split("\n", QString::SkipEmptyParts);

	myTableModel->clear();
	int maxColumns = 6;
	myTableModel->setColumnCount(maxColumns);

	int columns = 0;
	int row=0;

	QStringList::iterator line = lines.begin();
	for (;line != lines.end(); ++line)
	{

		QStringList components = (*line).split("\t",QString::SkipEmptyParts);

		if (columns==0)
		{
			if (components.size()>0)
			{
				columns = components.size();


				std::cout << lines.size()<<std::endl;
				std::cout << "Initializing "<<columns<<" columns\n";
			}
		}

		Transaction t = createTransaction( components );
		transactions.push_back(t);

		for (int col=0; col<columns && col<components.size(); ++col)
		{
			QStandardItem *item = new QStandardItem(components[col]);
			myTableModel->setItem(row, col, item);
		}

		row++;
	}

	transactionTable->setModel(myTableModel);
	transactionTable->show();

	show();
	raise();
	activateWindow();

	return transactionList;
}

Transaction SplitterDialog::createTransaction( QStringList components )
{
	Transaction t;
	t.transactionDate = QDateTime::fromString(components[0], "yy-mm-dd");
	t.description = components[2];
	t.amount = components[3].toDouble();
	t.balance = components[4].toDouble();

	return t;
}


void SplitterDialog::formatUserData()
{
	ClassifyDialog classifyDialog(this);

	// Todo: This implementation is crude.
	// It's possible to forget or make duplicate choices.
	for (unsigned i=0; i<columnComboBox.size(); ++i)
	{
		if (columnComboBox[i]->currentIndex() == indexTransactionDate)
			classifyDialog.setTextDate( textColumns[i]->toPlainText() );

		if (columnComboBox[i]->currentIndex() == indexTransactionDescription)
			classifyDialog.setTextDescription( textColumns[i]->toPlainText() );

		if (columnComboBox[i]->currentIndex() == indexTransactionAmount)
			classifyDialog.setTextAmount( textColumns[i]->toPlainText() );

	}

	classifyDialog.exec();


}

bool SplitterDialog::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::ContextMenu)
    {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent*> (event);
        QMenu *menu = new QMenu(this);

        // Todo: The offset below needs to be determined programmatically at runtime
        // See http://www.qtcentre.org/threads/50057-QTableView-rowAt()-gives-wrong-row-number-(aim-right-cklick-enabling)
        int offset = 5;
        int clickedRow = transactionTable->rowAt(mouseEvent->y()-offset*2);

        if (clickedRow != -1)
        {
        	QSignalMapper *signalMapper = new QSignalMapper(menu);

        	QAction *qa = new QAction(tr("Food"),this);
			QObject::connect(qa, SIGNAL(triggered()), signalMapper, SLOT(map()));
			SplitterWndwMenuArgs *args = new SplitterWndwMenuArgs(clickedRow, 1,menu);//(clickedRow,1);
			signalMapper->setMapping(qa, args);
			menu->addAction(qa);

	     	qa = new QAction(tr("Pleasure"),this);
			QObject::connect(qa, SIGNAL(triggered()), signalMapper, SLOT(map()));
			args = new SplitterWndwMenuArgs(clickedRow, 2,menu);//(clickedRow,1);
			signalMapper->setMapping(qa, args);
			menu->addAction(qa);

			connect(signalMapper, SIGNAL(mapped(QObject*)),
			             this, SLOT(setCategoryOfTransactionRow(QObject*)));

			menu->exec(mouseEvent->globalPos());
        }

        return false;
    }
    else
        return QDialog::eventFilter(obj, event);
}

void SplitterDialog::setCategoryOfTransactionRow(QObject* args)
{
	SplitterWndwMenuArgs *menuArgs = static_cast<SplitterWndwMenuArgs*> (args);
	std::cout << "Clicked cat "<<menuArgs->category<<" for row "<<menuArgs->row<<std::endl;

	transactions[menuArgs->row].primaryCategory = menuArgs->category;

	QBrush colour = Qt::blue;
	switch(menuArgs->category)
	{
		case 1:
			colour = Qt::blue;
			break;
		case 2:
			colour = Qt::red;
			break;
	}

	QStandardItem *cell = myTableModel->item(menuArgs->row-1,0);
	for (int i=0;cell;++i)
	{
		cell->setBackground(colour);
		cell = myTableModel->item(menuArgs->row-1,i);
	}

}

SplitterDialog::SplitterDialog(QWidget *parent)
	: QDialog(parent)
{

	installEventFilter(this);

	myTableModel = new QStandardItemModel();
	transactions.reserve(1000);


	// GUI

	btOk = new QPushButton(tr("&Next"));
	QObject::connect(btOk,SIGNAL(clicked()), this, SLOT(formatUserData()));

	btCancel = new QPushButton(tr("&Cancel"));
	QObject::connect(btCancel,SIGNAL(clicked()), this, SLOT(reject()));

	transactionTable = new QTableView();

	hlayoutUpper = new QHBoxLayout();

	hlayoutUpper->addWidget(transactionTable);

	hlayoutLower = new QHBoxLayout();
	hlayoutLower->addWidget(btOk);
	hlayoutLower->addWidget(btCancel);

	vlayout = new QVBoxLayout();
	vlayout->addLayout(hlayoutUpper);
	vlayout->addLayout(hlayoutLower);

	setLayout(vlayout);

	columnTypes.append( tr("None"));
	columnTypes.append( tr("Date"));
	columnTypes.append( tr("Description"));
	columnTypes.append( tr("Amount"));


}

SplitterDialog::~SplitterDialog()
{
	/*delete tableWidget;
	delete btOk;
	delete btCancel;*/
};


int ClassifyDialog::exec()
{
	std::cout << "Classify...\n";

	if (   textDate.size() == 0
		|| textDescription.size() == 0
		|| textAmount.size() == 0 )
	{
		QMessageBox popup(this);
		popup.setText( tr("Category seems empty"));
		popup.exec();

		return QDialog::Rejected;
	}


	QLabel lbDate;
	QLabel lbDescription;
	QLabel lbAmount;

	return QDialog::Accepted;

}

SplitterWndwMenuArgs::SplitterWndwMenuArgs(int _row,int _category, QObject *parent)
 : QObject( parent )
{
	row=_row;
	category=_category;
};
