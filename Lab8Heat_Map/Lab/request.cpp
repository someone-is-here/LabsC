#include "request.h"
#include <QFile>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QEventLoop>
#include <QJsonDocument>
#include <QJsonObject>

Request::Request(){
    manager = new QNetworkAccessManager(this);
}
void Request::MakeRequest(){
    QFile file("D:\\QT\\Projects\\Lab\\Result.txt");
    file.open(QIODevice::ReadWrite | QIODevice::Text);
    QFile fileWithCities("D:\\QT\\Projects\\Lab\\Cities.txt");
    fileWithCities.open(QIODevice::ReadWrite | QIODevice::Text);
    QEventLoop eventLoop;
    connect(manager, SIGNAL(finished(QNetworkReply*)), &eventLoop, SLOT(quit()));
    while(!fileWithCities.atEnd()){
        QNetworkRequest request;
        QString c = fileWithCities.readLine();
        QString baseUrl = "http://api.weatherstack.com/current?access_key=" + apiKey;
        QString query = "&query="+(c.remove('\n')+", Belarus");
        request.setUrl(baseUrl + query);
        QNetworkReply* reply = manager->get(request);
        eventLoop.exec();
        switch (reply->error()) {
        case QNetworkReply::NoError: {
            QString strReply = static_cast<QString>(reply->readAll());
            file.seek(file.size() - 1);
            if(file.size() > 0){
                  file.write("\n" + strReply.toUtf8());
            }else{
                  file.write(strReply.toUtf8());
            }
            QJsonDocument jsonResponse = QJsonDocument::fromJson(strReply.toUtf8());
            QJsonObject jsonObj = jsonResponse.object();
            delete reply;
            break;
        }
        default:
            qDebug() << "\nnetwork error occurred\n";
            break;
        }
    }
    fileWithCities.close();
    file.close();
}
void Request::OpenFile(){
    file0.setFileName("D:\\QT\\Projects\\Lab\\Result.txt");
    file0.open(QIODevice::ReadOnly | QIODevice::Text);
}
bool Request::IsEndOfFile(){
    return file0.atEnd();
}
void Request::ReadResultFromFile(){
    QString result = file0.readLine();
    if(!result.contains("}}")){
        result += "}";
    }
    QJsonDocument jsonResponse = QJsonDocument::fromJson(result.toUtf8());
    QJsonObject jsonObj = jsonResponse.object();
    x = jsonObj.value("location").toObject().value("lon").toString().toDouble();
    y = jsonObj.value("location").toObject().value("lat").toString().toDouble();
    temp = jsonObj.value("current").toObject().value("temperature").toInt();
    city = jsonObj.value("request").toObject().value("query").toString();
    city = city.remove(city.indexOf(','),city.length()-city.indexOf(','));
    pressure = jsonObj.value("current").toObject().value("pressure").toInt();
}
void Request::CloseFile(){
     file0.close();
}
Request::~Request(){
    manager->clearConnectionCache();
    delete manager;
}

