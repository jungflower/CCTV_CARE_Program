#ifndef EDITRESERVATIONDIALOG_H
#define EDITRESERVATIONDIALOG_H

#include <QDialog>
#include <QDateEdit>
#include <QTimeEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include "reservation.h"

class EditReservationDialog : public QDialog
{
    Q_OBJECT
public:
    explicit EditReservationDialog(const Reservation &res, QWidget *parent = nullptr);

    Reservation getUpdatedReservation() const;
    bool isDeleted() const;

private:
    QDateEdit *dateEdit;
    QTimeEdit *timeEdit;
    QPushButton *deleteButton;
    QPushButton *saveButton;

    Reservation original;
    bool deleted = false;
};

#endif // EDITRESERVATIONDIALOG_H
