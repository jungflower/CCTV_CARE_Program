
#include "widget.h"
#include "employeepage.h"
#include "scheduleregisterpage.h"
#include "scheduleviewpage.h"
#include <QVBoxLayout>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    //set 최소크기 지정
    //resize 수정




    resize(1200, 600);
    // QtabWidget 생성a
    tabWidget = new QTabWidget(this);
    // 각 페이지 위젯 생성
    employeePage = new EmployeePage(this);
    scheduleRegisterPage = new ScheduleRegisterPage(this);
    scheduleViewPage = new ScheduleViewPage(this);
    // 각 탭에 페이지 추가
    tabWidget->addTab(employeePage, "고객정보");
    tabWidget->addTab(scheduleRegisterPage, "서비스 예약 등록");
    tabWidget->addTab(scheduleViewPage, "예약 일정 조회");
    // 레이아웃에 추가
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(tabWidget);
    setLayout(mainLayout);

//     connect(employeePage, &EmployeePage::customerListUpdated,
//             scheduleRegisterPage, &ScheduleRegisterPage::onLoadClicked);
}
Widget::~Widget()
{
}
