#include "reservation.h"

Reservation::Reservation() {
    id = QUuid::createUuid().toString(QUuid::WithoutBraces);
    status = ReservationStatus::Pending;
}

QJsonObject Reservation::toJson() const {
    QJsonObject obj;
    obj["id"] = id;
    obj["customerId"] = customerId;
    obj["date"] = date.toString(Qt::ISODate);
    obj["time"] = time.toString("HH:mm");
    obj["status"] = statusToString(status);
    return obj;
}

Reservation Reservation::fromJson(const QJsonObject &obj) {
    Reservation r;
    r.id = obj["id"].toString();
    r.customerId = obj["customerId"].toString();
    r.date = QDate::fromString(obj["date"].toString(), Qt::ISODate);
    r.time = QTime::fromString(obj["time"].toString(), "HH:mm");
    r.status = stringToStatus(obj["status"].toString());
    return r;
}

