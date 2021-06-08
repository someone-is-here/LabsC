#ifndef COLORMAP_H
#define COLORMAP_H
#include <QWidget>
#include <QDebug>

class ColorMap : public QWidget{
protected:
    static uint rgbFromWaveLength(double wave);
    enum { ColormapSize = 512 };
    uint colorMap[ColormapSize];
    double centerX = 475;
    double centerY = 250;
    double scaleFactor = 0.0047;
public:
    ColorMap(QWidget *parent = nullptr);
    void render(double centerX, double centerY, double scaleFactor);
    void paintEvent(QPaintEvent * event) override;
    ~ColorMap()override;
};

#endif // COLORMAP_H
