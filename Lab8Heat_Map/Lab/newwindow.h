#ifndef NEWWINDOW_H
#define NEWWINDOW_H

#include <QDialog>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QPolygon>
#include <QPainter>
#include <QImage>
#include <QGraphicsBlurEffect>
#include "request.h"

namespace Ui {
class NewWindow;
}

class NewWindow : public QDialog{
    Q_OBJECT
public:
    explicit NewWindow(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent * /* event */);
    ~NewWindow();
private:
    Request request;
    Ui::NewWindow *ui;    
    int FromDoubleIntoScale(double value, double min, double max, int field);
};

#endif // NEWWINDOW_H


