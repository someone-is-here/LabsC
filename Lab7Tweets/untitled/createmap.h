#ifndef CREATEMAP_H
#define CREATEMAP_H
#include <QWidget>
#include <QPolygon>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QJsonObject>
#include <QDebug>
#include <QString>
#include <QList>
#include <QPainter>
#include <QRegularExpression>

class CreateMap: public QWidget{
    Q_OBJECT
private:
    QMap<QString , QList<QPolygon>> states;
    QMap<QString , double> balance;
    QList<QString> listWithSentiments;
    QList<double> sentimetsValues;
    double xMin = -180;
    int maxStep = 7;
    double xMax = -55;
    double yMin = 15;
    double yMax = 75;
    int FromDoubleIntoScale(double value, double min, double max, int field);
    void FindStep();
public:
    CreateMap();
    void ReadSentiments();
    void CreateList(QStringList &list);
    void paintEvent(QPaintEvent * event) override;
    void ReadTweets();
    void ReadJsonFile();
    void showBalance();
    void InFileResults();
    void ReadResultFile();
   ~CreateMap() override;
};

#endif // CREATEMAP_H
