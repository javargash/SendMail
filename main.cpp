#include "mainwindow.h"

#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTranslator translator;
    if (translator.load("qt_es", QLibraryInfo::location(QLibraryInfo::TranslationsPath))) {
        a.installTranslator(&translator);
    } else {
        qWarning("No se pudo cargar el archivo de traducción para español.");
    }

    MainWindow *w=new MainWindow(&a,0);
    //MainWindow w;
    w->show();
    return a.exec();
}
