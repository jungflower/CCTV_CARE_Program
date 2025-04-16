#ifndef SCHEDULEREGISTERPAGE_H
#define SCHEDULEREGISTERPAGE_H

#include <QWidget>
#include <QList>
#include <QMap>
#include "customer.h"
#include "reservation.h"
#include "ui_scheduleregisterpage.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ScheduleRegisterPage; }
QT_END_NAMESPACE

class ScheduleRegisterPage : public QWidget
{
    Q_OBJECT

public:
    explicit ScheduleRegisterPage(QWidget *parent = nullptr);
    ~ScheduleRegisterPage();

private:
    Ui::ScheduleRegisterPage *ui;
    QList<Customer> customers;
    QMap<QString /* customerId */, QList<Reservation>> reservationMap;
    QString selectedCustomerId;
    // resize ->
    // void resizeEvent(QResizeEvent *event);
    void refreshReservationTable(const QString &customerId);
    bool hasReservationConflict(const QString &id, const QDate &date, const QTime &time);
    void populateCustomerJsonArray(QJsonArray &array);

public slots:

    void onLoadClicked();

    // void onAppointmentItemChanged(QTableWidgetItem *item);
    // void resizeEvent(QResizeEvent *event);
private slots:
    void onCustomerSelected();
    void onAddReservationClicked();
    void onSaveClicked();
    void onCancelledClicked();
    void editReservation(const QString &id, const QDate &newDate, const QTime &newTime);

    void onCustomerSearchTextChanged(const QString &text);
    void onAppointmentCellDoubleClicked(int row, int column);
    void onAppointmentCellChanged(int row, int column);
};

#endif // SCHEDULEREGISTERPAGE_H
