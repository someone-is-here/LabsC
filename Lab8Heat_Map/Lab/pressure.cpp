#include "pressure.h"
#include "ui_pressure.h"
#include "request.h"

Pressure::Pressure(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Pressure){
    this->setBaseSize(1000, 1000);
    ui->setupUi(this);
    this->show();
}
void Pressure::paintEvent(QPaintEvent * /* event */){
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
    painter.drawText(35, 15, "800");
    painter.drawText(35, 105, "1000");
    painter.drawText(35, 195, "2000");

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
        if(request.pressure >= 1005){
            radialGrad.setColorAt(0, Qt::yellow);
            radialGrad.setColorAt(1, Qt::green);
        }else if(request.pressure >= 1000 && request.pressure < 1005){
            radialGrad.setColorAt(0, QColor("Green"));
            radialGrad.setColorAt(0.5, QColor("Green"));
            radialGrad.setColorAt(1, Qt::cyan);
        }else if(request.pressure < 1000){
            radialGrad.setColorAt(0, Qt::cyan);
            radialGrad.setColorAt(1, QColor("Purple"));
        }else{
            radialGrad.setColorAt(0, QColor("Blue"));
            radialGrad.setColorAt(1, QColor("White"));
        }
        painter.setBrush(radialGrad);
        painter.drawEllipse(x, this->height() - y, 50, 50);
        painter.setFont(QFont("Times", 10, QFont::Normal));

        painter.drawText(x + 10, this->height() - y + 35, QString::number(request.pressure));
        painter.drawText(x, this->height() - y + 60, request.city);
    }
    request.CloseFile();
}
int Pressure::FromDoubleIntoScale(double value, double min, double max, int field) {
    return static_cast<int>(((value - min) / (max - min)) * field);
}

Pressure::~Pressure(){
    delete ui;
}

