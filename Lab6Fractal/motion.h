#ifndef MOTION_H
#define MOTION_H

#include "colormap.h"
#include <QPoint>

class Motion : public ColorMap {
private:
    QPoint lastPos;
    double currScale;
    void scroll(int deltaX, int deltaY);
private slots:
    void zoom(double zoomFactor);
public:
    Motion(QWidget *parent = nullptr);
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    ~Motion() override;
};

#endif // MOTION_H
