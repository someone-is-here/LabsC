#include "pressureallrepublic.h"
#include "ui_pressureallrepublic.h"
#include "request.h"
#include <QtMath>

PressureAllRepublic::PressureAllRepublic(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PressureAllRepublic){
    this->setBaseSize(1000, 1000);
    ui->setupUi(this);
    this->show();
}

void PressureAllRepublic::paintEvent(QPaintEvent * /* event */){
    QImage image(this->width(), this->height(), QImage::Format_RGB32);
    image.fill(QColor("white"));
    QPainter painter(&image);

    QLinearGradient l = QLinearGradient(QPoint(0,0), QPoint(30,200));
    l.setColorAt(0, QColor(0,255,0));
    l.setColorAt(0.4, QColor(200,255,0));
    l.setColorAt(0.5, QColor(255,255,0));
    l.setColorAt(0.6, QColor(255,255,0));
    l.setColorAt(0.7, QColor(255,200,0));
    l.setColorAt(0.85, QColor(255,100,0));
    l.setColorAt(1, QColor(255,0,0));

    QRect rec(0,0,30,200);
    painter.setBrush(l);
    painter.fillRect(rec,l);
    painter.setBrush(QColor("Black"));
    painter.setFont(QFont("Times", 10, QFont::Normal));
    painter.drawText(35, 15, "800");
    painter.drawText(35, 105, "1000");
    painter.drawText(35, 195, "2000");

    painter.setBrush(QColor("White"));

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

    QPainter paint(this);
    paint.drawImage(0,0,image);

    request.OpenFile();

    while(!request.IsEndOfFile()){
        request.ReadResultFromFile();

        int x = FromDoubleIntoScale(request.x, 22, 34, this->width());
        int y = FromDoubleIntoScale(request.y, 50, 57, this->height());
        listWithPoints.append(QPoint(x,this->height() - y));
        pressure.append(request.pressure);
    }
    for(int i = 0; i < listWithPoints.size(); i++){
        if(image.pixelColor(listWithPoints[i].x(),listWithPoints[i].y()) != QColor("White")){continue;}
        if(pressure[i] <= 1000){
            image.setPixelColor(listWithPoints[i].x(),listWithPoints[i].y(),QColor(255 - (pressure[i]/100),255,0));
        } else{
            image.setPixelColor(listWithPoints[i].x(),listWithPoints[i].y(),QColor(255, 255 - 15 * (pressure[i]%1000) % 255, 0));
        }
        if(image.pixelColor(listWithPoints[i].x() + 1,listWithPoints[i].y()) == QColor("White")){
            listWithPoints.append(QPoint(listWithPoints[i].x() + 1,listWithPoints[i].y()));
            pressure.append(pressure[i]);
        }
        if(image.pixelColor(listWithPoints[i].x(),listWithPoints[i].y() + 1) == QColor("White")){
            listWithPoints.append(QPoint(listWithPoints[i].x(),listWithPoints[i].y() + 1));
            pressure.append(pressure[i]);
        }
        if(image.pixelColor(listWithPoints[i].x() - 1,listWithPoints[i].y()) == QColor("White")){
            listWithPoints.append(QPoint(listWithPoints[i].x() - 1,listWithPoints[i].y()));
            pressure.append(pressure[i]);
        }
        if(image.pixelColor(listWithPoints[i].x(),listWithPoints[i].y() - 1) == QColor("White")){
            listWithPoints.append(QPoint(listWithPoints[i].x(),listWithPoints[i].y() - 1));
            pressure.append(pressure[i]);
        }
    }

    request.CloseFile();
    paint.drawImage(0,0,image);
}

int PressureAllRepublic::FromDoubleIntoScale(double value, double min, double max, int field) {
    return static_cast<int>(((value - min) / (max - min)) * field);
}
PressureAllRepublic::~PressureAllRepublic(){
    delete ui;
}
