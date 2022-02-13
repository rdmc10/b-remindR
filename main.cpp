#include "mainwindow.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    //Setting stylesheet
    QFile ssFile("./SyNet.qss");
    ssFile.open(QFile::ReadOnly);
    QString ss= QLatin1String(ssFile.readAll());
    a.setStyleSheet(ss);

    w.show();
    return a.exec();
}
