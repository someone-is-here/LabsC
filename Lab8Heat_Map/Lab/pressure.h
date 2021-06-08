#ifndef PRESSURE_H
#define PRESSURE_H
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
class Pressure;
}

class Pressure : public QDialog {
    Q_OBJECT
public:
    explicit Pressure(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent * /* event */);
    ~Pressure();
private:
    Ui::Pressure *ui;
    Request request;
    int FromDoubleIntoScale(double value, double min, double max, int field);
};

#endif // PRESSURE_H




