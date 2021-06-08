//#include "createmap.h"
//#include <QFile>
//#include <QJsonDocument>
//#include <QJsonObject>
//#include <QJsonArray>
//#include <QPolygon>
//#include <QPainter>
//#include <QImage>

//CreateMap::CreateMap() {

//}
//void CreateMap::paintEvent(QPaintEvent* e) {
//    Q_UNUSED(e);
//    QPainter painter(this);
//    painter.setBrush(QColor("Yellow"));

//    QImage image(this->width(), this->height(), QImage::Format_RGB32);
//    painter.fillRect(rect(), image);

//    QFile file("D:\\QT\\Projects\\Lab\\blr1.json");
//    file.open(QIODevice::ReadOnly | QIODevice::Text);

//    QJsonDocument document = QJsonDocument::fromJson(file.readAll());
//    file.close();

//    QJsonObject json = document.object();
//    QStringList listWithKeys = json.keys();

//    for (int i = 0; i < listWithKeys.size(); i++) {
//        QJsonArray jsonArray = json[listWithKeys[i]].toArray();
//        QPolygon polygonValues;
//        for (int j = 0; j < jsonArray.size(); j++) {
//            QJsonArray newJsonArray = jsonArray[j].toArray();
//            int x = FromDoubleIntoScale(newJsonArray[0].toDouble(), 22, 34, this->width());
//            int y = FromDoubleIntoScale(newJsonArray[1].toDouble(), 50, 57, this->height());
//            polygonValues.putPoints(polygonValues.size(), 1, x, this->height() - y);
//        }
//        painter.drawPolygon(polygonValues);
//    }
//}
//int CreateMap::FromDoubleIntoScale(double value, double min, double max, int field) {
//    return static_cast<int>(((value - min) / (max - min)) * field);
//}
