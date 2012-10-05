

#ifndef MAINWINDOW_H_
#define MAINWINDOW_H_

#include <QtGui>
#include <QPushButton>
#include <QWidget>

#include "tools/DataImport.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QApplication *_app);
	~MainWindow() {};


protected:
	void closeEvent(QCloseEvent *event) {};

private:

	QApplication *app;

	void readSettings() {};
	void layoutWindow();


	QWidget *window;
	QHBoxLayout *layout;
	QPushButton *btOpenStatement;
	QPushButton *btQuit;

	SplitterDialog *splitterDialog;

private slots:

public slots:
	void openStatement(QString filename = "");


};


#endif
