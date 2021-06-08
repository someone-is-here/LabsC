#include "mainwindow.h"
#include "createmap.h"
#include <QApplication>
#include <QFile>
#include <QDebug>
#include <QIODevice>
#include <QString>

int main(int argc, char *argv[]){    
    QApplication a(argc, argv);

    CreateMap obj;
    obj.ReadJsonFile();
    obj.ReadTweets();
    obj.show();

    return a.exec();
}
