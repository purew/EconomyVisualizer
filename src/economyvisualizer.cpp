#include <QtGui/QtGui>


#include "tools/Transaction.h"
#include "tools/DataImport.h"
#include "MainWindow.h"



int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow mainWin(&app);
    mainWin.show();

   // mainWin.openStatement("data/data.dump");

    return app.exec();
}
