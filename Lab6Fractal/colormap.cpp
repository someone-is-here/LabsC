#include "colormap.h"
#include <math.h>
#include <QPainter>
#include <QDebug>

ColorMap::ColorMap(QWidget *parent) : QWidget(parent){
    this->setFixedSize(750, 500);
    for(int i = 1; i < ColormapSize; i++){
        colorMap[i] = rgbFromWaveLength(380.0 + (i * 400.0 / ColormapSize));
    }
}
uint ColorMap::rgbFromWaveLength(double value){
    double r = 0;
    double g = 0;
    double b = 0;

    if (value >= 380.0 && value <= 440.0) {
        r = 255;
    } else if (value >= 440.0 && value <= 490.0) {
        r = g = b = 255;
    } else if (value >= 490.0 && value <= 510.0) {
        r = 255;
    } else if (value >= 510.0 && value <= 580.0) {
        r = g = b = 0;
    } else if (value >= 580.0 && value <= 645.0) {
        r = 255;
    } else if (value >= 645.0 && value <= 780.0) {
        r = 167.0;
    }

    double s = 1.0;

    if (value > 700.0){
        s = 0.03 + 0.007 * (780.0 - value) / (780.0 - 700.0);
    } else if (value <  420.0){
        s = 0.03 + 0.007 * (value - 380.0) / (420.0 - 380.0);
    }

    r = std::pow(r * s, 0.8);
    g = std::pow(g * s, 0.8);
    b = std::pow(b * s, 0.8);

    return qRgb(int(r * 255), int(g * 255), int(b * 255));
}
void ColorMap::render(double centerX, double centerY, double scaleFactor){
    qDebug()<<"Render()";
    this->centerX = centerX;
    this->centerY = centerY;
    this->scaleFactor = scaleFactor;
    qDebug()<<centerX<<" "<<centerY<<" "<<scaleFactor;
}

void ColorMap::paintEvent(QPaintEvent * /* event */){
    qDebug()<<"Paint()";
    QPainter painter(this);
    QImage image(this->width(), this->height(), QImage::Format_RGB32);
    const int n = 255;
    const double max = 2;
    double x = 0, y = 0, x1 = 0, y1 = 0, cx = 0, cy = 0;
    int i = 1;
    for(int ix = 0; ix < image.width(); ix++){
        for(int iy = 0; iy < image.height(); iy++){
            x = 0; y = 0;
            cx = scaleFactor * (ix - centerX);
            cy = scaleFactor * (iy - centerY);
            for(i = 1; i < n; i++){
                x1 = x * x - y * y + cx;
                y1 = 2 * x * y + cy;
                if(x1 > max || y1 > max){
                    break;
                }
                x = x1;
                y = y1;
            }
            image.setPixelColor(ix, iy, colorMap[i]);
        }
    }
    painter.fillRect(rect(), image);
}
ColorMap::~ColorMap(){
    centerX = 0;
    centerY = 0;
    scaleFactor = 0;
}
