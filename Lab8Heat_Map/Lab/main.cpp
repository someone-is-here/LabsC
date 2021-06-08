#include "mainwindow.h"
#include <QApplication>
#include "request.h"

int main(int argc, char *argv[]){
    QApplication a(argc, argv);

    MainWindow w;
    //Request rec;
    //rec.MakeRequest();
    w.show();

    return a.exec();
}
