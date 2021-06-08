#include "motion.h"
#include "math.h"
#include <QWheelEvent>
#include <QKeyEvent>

const double DefaultScale = 0.0035;
const double ZoomInFactor = 0.8;
const double ZoomOutFactor = 1 / ZoomInFactor;
const int ScrollStep = 50;

Motion::Motion(QWidget *parent) : ColorMap(parent), currScale(DefaultScale){
    setWindowTitle(tr("Beauty"));
}
void Motion::scroll(int dX, int dY){
    qDebug()<<"scroll()";
    centerX += dX * 2;
    centerY += dY * 2;
    render(centerX, centerY, currScale);
    update();
}
void Motion::zoom(double zoomFactor){
    qDebug()<<currScale<< " scale";
    currScale *= zoomFactor;
    centerX += (centerX - centerX * zoomFactor) / sqrt(2);
    centerY += (centerY - centerY * zoomFactor*zoomFactor) / sqrt(2);
    render(centerX, centerY, currScale);
    update();
}
void Motion::wheelEvent(QWheelEvent *event){
    qDebug()<<"Wheel Event()";
    const int numDegrees = (event->angleDelta().y() / 8);
    const double numSteps = numDegrees / double(15);
    zoom(pow(ZoomInFactor, numSteps));
}
void Motion::mousePressEvent(QMouseEvent *event){
     qDebug()<<"MousePressEvent()";
    if (event->button() == Qt::LeftButton){
        lastPos = event->pos();
    }
}

void Motion::mouseMoveEvent(QMouseEvent *event){
     qDebug()<<"MouseMoveEvent()";
    if (event->buttons() & Qt::LeftButton) {
        scroll(event->pos().x() - lastPos.x(), event->pos().y() - lastPos.y());
        lastPos = event->pos();
        update();
    }
}

void Motion::keyPressEvent(QKeyEvent *event){
    qDebug()<<"KeyPressEvent()";
    switch (event->key()) {
    case Qt::Key_Plus:
        zoom(ZoomInFactor);
        break;
    case Qt::Key_Minus:
        zoom(ZoomOutFactor);
        break;
    case Qt::Key_Left:
        scroll(+ScrollStep, 0);
        break;
    case Qt::Key_Right:
        scroll(-ScrollStep, 0);
        break;
    case Qt::Key_Down:
        scroll(0, -ScrollStep);
        break;
    case Qt::Key_Up:
        scroll(0, +ScrollStep);
        break;
    default:
        QWidget::keyPressEvent(event);
    }
}
Motion::~Motion(){
    currScale = 0;
}
