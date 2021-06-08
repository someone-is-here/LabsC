#include "temperatureallrepublic.h"
#include "ui_temperatureallrepublic.h"
#include <QtMath>

TemperatureAllRepublic::TemperatureAllRepublic(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TemperatureAllRepublic){

    this->setBaseSize(1000, 1000);
    ui->setupUi(this);
    this->show();
}

void TemperatureAllRepublic::paintEvent(QPaintEvent * /* event */){
    QImage image(this->width(), this->height(), QImage::Format_RGB32);
    image.fill(QColor("white"));
    QPainter painter(&image);

    QLinearGradient l = QLinearGradient(QPoint(0,0), QPoint(30,200));
    l.setColorAt(0, QColor(0,0,255));
    l.setColorAt(0.1, QColor(50,105,255));
    l.setColorAt(0.2, QColor(100,205,255));
    l.setColorAt(0.3, QColor(100,245,255));
    l.setColorAt(0.4, QColor(90,255,170));
    l.setColorAt(0.5, QColor(50,255,30));
    l.setColorAt(0.6, QColor(170,255,100));
    l.setColorAt(0.7, QColor(255,255,30));
    l.setColorAt(0.75, QColor(255,240,0));
    l.setColorAt(0.85, QColor(255,190,0));
    l.setColorAt(0.95, QColor(255,100,0));
    l.setColorAt(1, QColor(255,0,0));

    QRect rec(0,0,30,200);
    painter.setBrush(l);
    painter.fillRect(rec,l);
    painter.setBrush(QColor("Black"));
    painter.setFont(QFont("Times", 10, QFont::Normal));
    painter.drawText(35, 15, "<-40");
    painter.drawText(35, 35, "-30");
    painter.drawText(35, 50, "-20");
    painter.drawText(35, 65, "-10");
    painter.drawText(35, 85, "0");
    painter.drawText(35, 110, "+10");
    painter.drawText(35, 135, "+20");
    painter.drawText(35, 170, "+30");
    painter.drawText(35, 195, ">+40");

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
        temperature.append(request.temp);
    }
    for(int i = 0; i < listWithPoints.size(); i++){
        if(image.pixelColor(listWithPoints[i].x(),listWithPoints[i].y()) != QColor("White")){continue;}
        if(temperature[i] < 0){
            image.setPixelColor(listWithPoints[i].x(),listWithPoints[i].y(),QColor(0, 0, 255 + (temperature[i]/100)));
        } else{
            image.setPixelColor(listWithPoints[i].x(),listWithPoints[i].y(),QColor((90 + 10 * temperature[i]%1000)%255, 255, 70));
        }
        if(image.pixelColor(listWithPoints[i].x() + 1,listWithPoints[i].y()) == QColor("White")){
            listWithPoints.append(QPoint(listWithPoints[i].x() + 1,listWithPoints[i].y()));
            temperature.append(temperature[i]);
        }
        if(image.pixelColor(listWithPoints[i].x(),listWithPoints[i].y() + 1) == QColor("White")){
            listWithPoints.append(QPoint(listWithPoints[i].x(),listWithPoints[i].y() + 1));
            temperature.append(temperature[i]);
        }
        if(image.pixelColor(listWithPoints[i].x() - 1,listWithPoints[i].y()) == QColor("White")){
            listWithPoints.append(QPoint(listWithPoints[i].x() - 1,listWithPoints[i].y()));
            temperature.append(temperature[i]);
        }
        if(image.pixelColor(listWithPoints[i].x(),listWithPoints[i].y() - 1) == QColor("White")){
            listWithPoints.append(QPoint(listWithPoints[i].x(),listWithPoints[i].y() - 1));
            temperature.append(temperature[i]);
        }
    }

    request.CloseFile();
    paint.drawImage(0,0,image);

}

int TemperatureAllRepublic::FromDoubleIntoScale(double value, double min, double max, int field) {
    return static_cast<int>(((value - min) / (max - min)) * field);
}
TemperatureAllRepublic::~TemperatureAllRepublic(){
    delete ui;
}
