#pragma once
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QMessageBox>
#include "reservation.h"
#include "customer.h"

class ReservationItem : public QGraphicsRectItem {
public:
    ReservationItem(const Reservation &res, const Customer &cust, const QRectF &rect);

protected:
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event) override;

private:
    Reservation reservation;
    Customer customer;
};
