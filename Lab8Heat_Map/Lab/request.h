#ifndef REQUEST_H
#define REQUEST_H
#include <QObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QFile>

class Request : public QObject{
private:
    QNetworkAccessManager* manager;
    const QString apiKey = "9ab5c17420def6058884c19f965265d2";
    QFile file0;
public:
    double y;
    double x;
    int temp;
    QString city;
    int pressure;
    Request();
    void MakeRequest();
    void OpenFile();
    void CloseFile();
    bool IsEndOfFile();
    void ReadResultFromFile();
    ~Request();
};

#endif // REQUEST_H
