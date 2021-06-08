#ifndef TEMPERATUREALLREPUBLIC_H
#define TEMPERATUREALLREPUBLIC_H

#include <QDialog>
#include "request.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QPolygon>
#include <QPainter>
#include <QImage>
#include <QGraphicsBlurEffect>

namespace Ui {
class TemperatureAllRepublic;
}

class TemperatureAllRepublic : public QDialog{
    Q_OBJECT
public:
    explicit TemperatureAllRepublic(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent * /* event */);
    int FromDoubleIntoScale(double value, double min, double max, int field);
    ~TemperatureAllRepublic();
private:
    Ui::TemperatureAllRepublic *ui;
    Request request;
    QList<int> temperature;
    QList<QPoint> listWithPoints;
};

#endif // TEMPERATUREALLREPUBLIC_H
