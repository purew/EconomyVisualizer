
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QFile>

#include <iostream>

#include "MainWindow.h"


MainWindow::MainWindow(QApplication *_app)
{
	app = _app;

	window = 0;
	readSettings();
	layoutWindow();

	splitterDialog = new SplitterDialog( this );

}


void MainWindow::layoutWindow()
{
	if (window==0)
	{

		btOpenStatement = new QPushButton(tr("&Open statement"));
		QObject::connect( btOpenStatement, SIGNAL(clicked()),this, SLOT(openStatement()));

		btQuit = new QPushButton(tr("&Quit"));
		QObject::connect( btQuit, SIGNAL(clicked()), app, SLOT(quit()));

		layout = new QHBoxLayout();
		layout->addWidget(btOpenStatement);
		layout->addWidget(btQuit);

		window = new QWidget();
		window->setLayout( layout );

		setCentralWidget(window);

	}
}

void MainWindow::openStatement(QString filename)
{
	if (filename == "")
		filename = QFileDialog::getOpenFileName(this,tr("Open statement"),".", "*");

	QFile file(filename);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		std::cerr << "Could not open " << filename.toStdString()<<std::endl;
		return;
	}

	int bufSize = 1024*1024;
	char buf[bufSize];
	QString fileContents;
	fileContents.reserve(bufSize);

	qint64 lineLength = 0;

	for(;;)
	{
		lineLength = file.readLine(buf, sizeof(buf));
		if (lineLength == -1)
			break;
		fileContents.append(buf);
	}

	file.close();

	std::cout << "Read "<<fileContents.size()<<" char's from file\n";


	splitterDialog->splitIntoTransactions(fileContents);


}
