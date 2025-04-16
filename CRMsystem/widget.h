#ifndef WIDGET_H
#define WIDGET_H
#include <QWidget>
#include <QPushButton>
#include <QTabWidget>
class EmployeePage;
class ScheduleRegisterPage;
class ScheduleViewPage;
class Widget : public QWidget
{
    Q_OBJECT
public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private:
    // 탭 전환
    QTabWidget *tabWidget;
    EmployeePage *employeePage;
    ScheduleRegisterPage *scheduleRegisterPage;
    ScheduleViewPage *scheduleViewPage;
};
#endif // WIDGET_H
