#pragma once

#include <QWidget>
#include <QGraphicsScene>
#include <QMap>
#include <QDate>
#include "reservation.h"
#include "customer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ScheduleViewPage; }
QT_END_NAMESPACE

class ScheduleViewPage : public QWidget
{
    Q_OBJECT

public:
    explicit ScheduleViewPage(QWidget *parent = nullptr);
    ~ScheduleViewPage();

public slots:
    // void loadData();
    void onLoadClicked();

private slots:
    void onDateChanged();

private:
    Ui::ScheduleViewPage *ui;
    QGraphicsScene *scene;

    QList<Customer> customers;
    QMap<QString, QList<Reservation>> reservationMap; // customerId -> 예약 목록

    void resizeEvent(QResizeEvent *event);
    void drawGanttChart(const QDate &date);
    void loadFromFile();
    QString getCustomerNameById(const QString &id);
};
