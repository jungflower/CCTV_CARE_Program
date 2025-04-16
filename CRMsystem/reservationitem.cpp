
#include "reservationitem.h"

ReservationItem::ReservationItem(const Reservation &res, const Customer &cust, const QRectF &rect)
    : QGraphicsRectItem(rect), reservation(res), customer(cust)
{
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsSelectable);
}

void ReservationItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    QString info = QString("회사명: %1\n담당자: %2\n연락처: %3\n메모: %4\n날짜: %5\n시간: %6 ~ %7")
                       .arg(customer.company())
                       .arg(customer.manager())
                       .arg(customer.phone())
                       .arg(customer.memo())
                       .arg(reservation.date.toString("yyyy-MM-dd"))
                       .arg(reservation.time.toString("HH:mm"))
                       .arg(reservation.time.addSecs(7200).toString("HH:mm"));  // 2시간 고정

    QMessageBox::information(nullptr, "예약 상세 정보", info);
}
