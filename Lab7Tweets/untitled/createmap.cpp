#include "createmap.h"

CreateMap::CreateMap(){
    this->resize(1500,1000);
}
void CreateMap::paintEvent(QPaintEvent * /* event */){
    QPainter painter(this);
    painter.setBrush(QColor("Yellow"));
    int r = 173, g = 255, b = 47;
    QImage image(this->width(), this->height(), QImage::Format_RGB32);
    painter.fillRect(rect(), image);
    auto iterBalance = balance.begin();
    auto iterForMap = states.begin();
    while(iterBalance != balance.end()){
        if(iterBalance.value() <= 0){
            r=255; g=0; b=0;
            r += static_cast<int>(iterBalance.value());
            g -= static_cast<int>(iterBalance.value());
            b -= static_cast<int>(iterBalance.value());
        }else if(iterBalance.value()/*/10*/>100){
            r=0; g=255; b=0;
            r += static_cast<int>(iterBalance.value()/*/10*/)%10;
            g -= static_cast<int>(iterBalance.value()/*/10*/)%10;
            b += static_cast<int>(iterBalance.value()/*/10*/)%10;
        }else if(iterBalance.value()/*/10*/<100 && iterBalance.value()/*/10*/>80){
            r=173; g=255; b=47;
            r += static_cast<int>(iterBalance.value()/*/10*/)%10;
            g -= static_cast<int>(iterBalance.value()/*/10*/)%10;
            b += static_cast<int>(iterBalance.value()/*/10*/)%10;
        } else if(iterBalance.value()/*/10*/<80 && iterBalance.value()/*/10*/>60){
            r = 255; g = 255; b = 0;
            r -= static_cast<int>(iterBalance.value()/*/10*/);
            g -= static_cast<int>(iterBalance.value()/*/10*/);
            b += static_cast<int>(iterBalance.value()/*/10*/);
        } else if(iterBalance.value()/*/10*/<60 && iterBalance.value()/*/10*/>30){
            r = 255; g = 216; b = 0;
            r -= static_cast<int>(iterBalance.value()/*/10*/);
            g -= static_cast<int>(iterBalance.value()/*/10*/);
            b += static_cast<int>(iterBalance.value()/*/10*/);
         }
        else {
            r = 255; g = 0; b = 255;
            r -= static_cast<int>(iterBalance.value()/*/10*/);
            g += static_cast<int>(iterBalance.value()/*/10*/);
            b -= static_cast<int>(iterBalance.value()/*/10*/);
        }

        painter.setBrush(QColor(r%256,g%256,b%256));

        for(int i=0;i<iterForMap.value().size();i++){
          painter.drawPolygon(iterForMap.value()[i]);
        }

        iterBalance++;
        iterForMap++;
    }
}
void CreateMap::ReadJsonFile(){
    QFile file("D:\\QT\\Projects\\untitled\\states.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QJsonDocument document = QJsonDocument::fromJson(file.readAll());
    file.close();

    QJsonObject json = document.object();
    QStringList listWithKeys = json.keys();

    for( int i = 0; i < listWithKeys.size(); i++){
        QJsonArray jsonArray = json[listWithKeys[i]].toArray();
        for(int j = 0; j < jsonArray.size(); j++){
             QJsonArray newJsonArray = jsonArray[j].toArray();
             QPolygon polygonValues;
             for(int k = 0; k < newJsonArray.size(); k++){
                 QJsonArray newJsonArray1 = newJsonArray[k].toArray();
                 for(int m = 0; m < newJsonArray1.size(); m++){
                     QJsonArray coords = newJsonArray1;
                     if(coords[m].toArray().size() > 0){
                         coords = coords[m].toArray();
                     }
                     int x = FromDoubleIntoScale(coords[0].toDouble(),xMin,xMax,this->width());
                     int y = FromDoubleIntoScale(coords[1].toDouble(),yMin,yMax,this->height());
                     polygonValues.putPoints(polygonValues.size(),1,x,this->height() - y);
                 }

             }
             states[listWithKeys[i]].append(polygonValues);
             balance[listWithKeys[i]] = 0.0;
        }
    }
}
int CreateMap::FromDoubleIntoScale(double value,double min,double max, int field){
    return static_cast<int>(((value - min)/(max - min)) * field);
}
void CreateMap::ReadSentiments(){
    QFile fileWithSentiments("D:\\QT\\Projects\\untitled\\sentiments.csv");
    fileWithSentiments.open(QIODevice::ReadOnly | QIODevice::Text);
    QString str;
    QStringList list;

    while(!fileWithSentiments.atEnd()){
        str = fileWithSentiments.readLine();
        list = str.split(QRegularExpression(","));
        listWithSentiments.append(list[0]);
        sentimetsValues.append(list[1].toDouble());
    }

    fileWithSentiments.close();
}
void CreateMap::CreateList(QStringList &list){
    int num = list.size();
    int step = 2;
    QString str;
    while(step < maxStep){
        for(int i = 0; i < num - 1; i++){
            str="";
            for(int j = 0; j < step; j++){
                if(i + j < num){
                    str += list[i + j];
                    if(j + 1 != step){
                        str += " ";
                    }
                } else{
                    str="";
                    break;
                }
            }
            if(str != ""){
                list.append(str);
            }
        }
        step++;
    }

}
void CreateMap::InFileResults(){
    QFile fileForWrite("D:\\QT\\Projects\\untitled\\Results.txt");
    fileForWrite.open(QIODevice::WriteOnly);
    QTextStream stream(&fileForWrite);
    auto iter = balance.begin();
    while(iter != balance.end()){
        stream << iter.key() << iter.value()<<'\n';
        iter++;
    }
    fileForWrite.close();
}
void CreateMap::ReadTweets(){
    ReadSentiments();
    FindStep();
    QFile file("D:\\QT\\Projects\\untitled\\smalltweets.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QString str;
    QStringList list;
    QStringList coords;
    double res;
    while(!file.atEnd()){
        res = 0;
        str = file.readLine();
        list = str.split(QRegularExpression("\t"));
        if(list[0].contains("[")){
            coords = list[0].split(QRegularExpression(","));
            QPoint point(FromDoubleIntoScale(coords[1].remove("]").toDouble(),xMin,xMax,this->width()), this->height() - FromDoubleIntoScale(coords[0].remove("[").toDouble(),yMin,yMax,this->height()));
            str = list[list.size()-1];
            list = str.split(QRegularExpression(" "));
            list[list.size()-1].remove('\n');
            CreateList(list);
            for(int i = 0; i < list.size(); i++){
                if(listWithSentiments.contains(list[i])){
                    res += sentimetsValues[listWithSentiments.indexOf(list[i])];
                }
            }
            auto iterForMap = states.begin();
            while(iterForMap!=states.end()){
                for(int i=0;i<iterForMap.value().size();i++){
                    if(iterForMap.value()[i].containsPoint(point, Qt::OddEvenFill)){
                        balance[iterForMap.key()] += res;
                    }
                }
                iterForMap++;
            }
        }
    }
    file.close();
}

void CreateMap::ReadResultFile(){
    QFile file("D:\\QT\\Projects\\untitled\\Results.txt");
    file.open(QIODevice::ReadOnly);
    auto iter = balance.begin();
    QStringList list;
    QString str;
    while(iter != balance.end()){
        str = file.readLine();
        list = str.split(QRegularExpression(" "));
        balance[list[0]] = list[1].toDouble();
        list = str.split(QRegularExpression(" "));
        balance[list[0]] = list[1].toDouble();
        iter++;
    }
    file.close();
}

void CreateMap::showBalance(){
    auto iter = balance.begin();
    while(iter != balance.end()){
        qDebug() << iter.key() << iter.value();
        iter++;
    }
}
void CreateMap::FindStep(){
    QStringList list;
    int max = 0;
    for(int i = 0; i < listWithSentiments.size(); i++){
        list = listWithSentiments[i].split(QRegularExpression(" "));
        if(list.size() > max){
            max = list.size();
        }
    }
    maxStep = list.size() - 1;
}

CreateMap::~CreateMap(){
    states.clear();
    balance.clear();
    listWithSentiments.clear();
    sentimetsValues.clear();
    xMin = 0;
    xMax = 0;
    yMin = 0;
    yMax = 0;
    maxStep = 0;
}
