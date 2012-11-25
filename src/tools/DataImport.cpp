
#include <iostream>

#include <QStringList>
#include <QPushButton>

#include "DataImport.h"




std::list<Transaction> SplitterDialog::splitIntoTransactions(QString str)
{
	std::list<Transaction> transactionList;

	QStringList lines = str.split("\n", QString::SkipEmptyParts);

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

				// Initialize columns
				for (int i=0; i<columns; ++i)
				{
					columnLayouts.push_back(new QVBoxLayout());

					columnComboBox.push_back(new QComboBox());
					columnComboBox[i]->addItems(columnTypes);
					columnLayouts[i]->addWidget(columnComboBox[i]);

					textColumns.push_back(new QPlainTextEdit());
					textColumns[i]->setReadOnly(true);
					columnLayouts[i]->addWidget(textColumns[i]);

					hlayoutUpper->addLayout(columnLayouts[i]);
				}
			}
		}


		for (int col=0; col<columns && col<components.size(); ++col)
		{
			textColumns[col]->appendPlainText(components[col]);
		}
		row++;

		//Transaction t;
		//t.transactionDate = QDateTime::fromString(components[0], "yy-mm-dd");

	}



	show();
	raise();
	activateWindow();

	return transactionList;
}

void SplitterDialog::formatUserData()
{
	ClassifyDialog classifyDialog;

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
}

SplitterDialog::SplitterDialog(QWidget *parent)
	: QDialog(parent)
{

	btOk = new QPushButton(tr("&Next"));
	QObject::connect(btOk,SIGNAL(clicked()), this, SLOT(formatUserData()));

	btCancel = new QPushButton(tr("&Cancel"));
	QObject::connect(btCancel,SIGNAL(clicked()), this, SLOT(reject()));

	hlayoutUpper = new QHBoxLayout();

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




void ClassifyDialog::setTextDate( const QString text)
{
	std::cout << "Setting date\n";
}

void ClassifyDialog::setTextDescription( const QString text)
{
	std::cout << "Setting Description\n";
}

void ClassifyDialog::setTextAmount( const QString text)
{
	std::cout << "Setting Amount\n";
}
