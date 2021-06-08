#include "newwindow.h"
#include "ui_newwindow.h"
#include "request.h"

NewWindow::NewWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewWindow){
    this->setBaseSize(1000,1000);
    ui->setupUi(this);
    this->show();
}
void NewWindow::paintEvent(QPaintEvent * /* event */){
    QPainter painter(this);

    QLinearGradient l = QLinearGradient(QPoint(0,0),QPoint(30,200));
    l.setColorAt(0, Qt::blue);
    l.setColorAt(0.4, QColor("Purple"));
    l.setColorAt(0.5, Qt::cyan);
    l.setColorAt(0.6, Qt::green);
    l.setColorAt(0.8, Qt::yellow);
    l.setColorAt(0.95, Qt::red);

    QRect rec(0,0,30,200);
    painter.setBrush(l);
    painter.fillRect(rec,l);
    painter.setBrush(QColor("Black"));
    painter.setFont(QFont("Times", 10, QFont::Normal));
    painter.drawText(35, 15, "<-40");
    painter.drawText(35, 35, "-30");
    painter.drawText(35, 50, "-10");
    painter.drawText(35, 75, "+0");
    painter.drawText(35, 105, "+10");
    painter.drawText(35, 135, "+20");
    painter.drawText(35, 175, "+30");
    painter.drawText(35, 195, ">40");

    QLinearGradient gradient(62, this->height() - 62, 572, this->height() - 422);
    gradient.setColorAt(0.0, Qt::green);
    gradient.setColorAt(0.25, Qt::blue);
    gradient.setColorAt(0.5, Qt::green);
    gradient.setColorAt(0.75, Qt::blue);
    gradient.setColorAt(1.0, Qt::green);

    painter.setBrush(gradient);

    QFile file("D:\\QT\\Projects\\Lab\\blr1.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QJsonDocument document = QJsonDocument::fromJson(file.readAll());
    file.close();

    QJsonObject json = document.object();
    QStringList listWithKeys = json.keys();

    for (int i = 0; i < listWithKeys.size(); i++) {
        QJsonArray jsonArray = json[listWithKeys[i]].toArray();
        QPolygon polygonValues;
        for (int j = 0; j < jsonArray.size(); j++) {
            QJsonArray newJsonArray = jsonArray[j].toArray();
            int x = FromDoubleIntoScale(newJsonArray[0].toDouble(), 22, 34, this->width());
            int y = FromDoubleIntoScale(newJsonArray[1].toDouble(), 50, 57, this->height());
            polygonValues.putPoints(polygonValues.size(), 1, x, this->height() - y);
        }
        painter.drawPolygon(polygonValues);
    }

    request.OpenFile();
    for(int i = 0; i < 6; i++){
        request.ReadResultFromFile();

        int x = FromDoubleIntoScale(request.x, 22, 34, this->width());
        int y = FromDoubleIntoScale(request.y, 50, 57, this->height());

        QRadialGradient radialGrad(x, this->height() - y, 50);
        if(request.temp >= 20 && request.temp < 24){
            radialGrad.setColorAt(0, Qt::yellow);
            radialGrad.setColorAt(1, Qt::green);
        }else if(request.temp >= 10 && request.temp < 15){
            radialGrad.setColorAt(0, QColor("Green"));
            radialGrad.setColorAt(1, Qt::cyan);
        }else if(request.temp >= 15 && request.temp < 20){
             radialGrad.setColorAt(0, Qt::green);
             radialGrad.setColorAt(1, QColor("darkGreen"));
        }else if(request.temp >= 24 && request.temp < 30){
            radialGrad.setColorAt(0, Qt::green);
            radialGrad.setColorAt(1, Qt::yellow);
        }else if(request.temp >= 30 && request.temp < 40){
            radialGrad.setColorAt(0, Qt::yellow);
            radialGrad.setColorAt(1, Qt::red);
        }else if( request.temp >= 40){
            radialGrad.setColorAt(0, Qt::red);
            radialGrad.setColorAt(1, Qt::yellow);
        }else if(request.temp >= 0 &&request.temp < 10){
            radialGrad.setColorAt(0, Qt::cyan);
            radialGrad.setColorAt(1, QColor("Purple"));
        }else if(request.temp < 0 &&request.temp >= -10){
            radialGrad.setColorAt(0, QColor("Purple"));
            radialGrad.setColorAt(1, QColor("darkBlue"));
        }else if(request.temp < -10 &&request.temp >= -30){
            radialGrad.setColorAt(0, QColor("darkBlue"));
            radialGrad.setColorAt(1, QColor("Blue"));
        }else{
            radialGrad.setColorAt(0, QColor("Blue"));
            radialGrad.setColorAt(1, QColor("White"));
        }
        painter.setBrush(radialGrad);
        painter.drawEllipse(x, this->height() - y, 50, 50);
        painter.setFont(QFont("Times", 10, QFont::Normal));

        painter.drawText(x + 10, this->height() - y + 35, "+" + QString::number(request.temp));
        painter.drawText(x, this->height() - y + 60, request.city);
    }
    request.CloseFile();
}
int NewWindow::FromDoubleIntoScale(double value, double min, double max, int field) {
    return static_cast<int>(((value - min) / (max - min)) * field);
}

NewWindow::~NewWindow()
{
    delete ui;
}
