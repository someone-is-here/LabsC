#ifndef PRESSUREALLREPUBLIC_H
#define PRESSUREALLREPUBLIC_H
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
class PressureAllRepublic;
}

class PressureAllRepublic : public QDialog{
    Q_OBJECT
public:
    explicit PressureAllRepublic(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent * /* event */);
    ~PressureAllRepublic();
private:
    Ui::PressureAllRepublic *ui;
    Request request;
    int FromDoubleIntoScale(double value, double min, double max, int field);
    QList<int> pressure;
    QList<QPoint> listWithPoints;
};

#endif // PRESSUREALLREPUBLIC_H




