#include "mainwindow.h"
#include <QApplication>
#include "motion.h"

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    Motion obj;
    obj.show();
    return a.exec();
}
