#include "datamanager.h"
#include <qjsonarray.h>



void DataManager::save(const QList<Customer> &customers, const QMap<QString, QList<Reservation> > &reservationMap)
{
    QJsonObject root;
    QJsonArray customerArray;
    for (const Customer&c : customers) {
        customerArray.append(c.toJson());
    }
    root["customers"]=customerArray;

    QJsonArray reservationArray;
    for (auto it = reservationMap.constBegin(); it != reservationMap.constEnd() ; ++it) {
        for (const Reservation& r: it.value()){
            reservationArray.append(r.toJson());
        }
    }
    root["reservations"]=reservationArray;

    QFile file("data.json");
    if(file.open(QIODevice::WriteOnly)){
        QJsonDocument doc(root);
        file.write(doc.toJson());
        file.close();
    }
}

void DataManager::load(QList<Customer> &customers, QMap<QString, QList<Reservation> > &reservationMap)
{
    QFile file("data.json");
    if (!file.open(QIODevice::ReadOnly)) return;

    QByteArray data=file.readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject root = doc.object();

    customers.clear();
    reservationMap.clear();

    QJsonArray customerArray = root["customers"].toArray();
    for (const QJsonValue& val : customerArray){
        customers.append(Customer::fromJson(val.toObject()));
    }

    QJsonArray reservationArray = root["reservations"].toArray();
    for (const QJsonValue& val : reservationArray){
        Reservation r = Reservation::fromJson(val.toObject());
        reservationMap[r.customerName].append(r);
    }

    file.close();
}
