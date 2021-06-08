#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "newwindow.h"
#include "pressure.h"
#include "pressureallrepublic.h"
#include "temperatureallrepublic.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);
}

void MainWindow::on_pushButton_clicked(){
    NewWindow window;
    window.setModal(true);
    window.exec();
}

void MainWindow::on_pushButton_2_clicked(){
    Pressure pressure;
    pressure.setModal(true);
    pressure.exec();
}

void MainWindow::on_pushButton_3_clicked(){
    PressureAllRepublic obj;
    obj.setModal(true);
    obj.exec();
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_pushButton_4_clicked(){
    TemperatureAllRepublic temp;
    temp.setModal(true);
    temp.exec();
}
