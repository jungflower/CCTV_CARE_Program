#ifndef RESERVATION_H
#define RESERVATION_H

#include <QString>
#include <QDate>
#include <QTime>
#include <QJsonObject>
#include <QUuid>

//예약 상태 데이터 구조 확장함
enum class ReservationStatus { Pending, Completed };

inline QString statusToString(ReservationStatus status) {
    return status == ReservationStatus::Completed ? "Completed" : " ";
}

inline ReservationStatus stringToStatus(const QString &str) {
    return str == "Completed" ? ReservationStatus::Completed : ReservationStatus::Pending;
}


struct Reservation {
    QString id;
    QString customerId;
    // QString customerName;
    QDate date;
    QTime time;
    ReservationStatus status = ReservationStatus::Pending;  //기본 pending 상태임

    Reservation();

    QJsonObject toJson() const;
    static Reservation fromJson(const QJsonObject &obj);
};

#endif // RESERVATION_H
