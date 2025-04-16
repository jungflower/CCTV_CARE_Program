/********************************************************************************
** Form generated from reading UI file 'scheduleregisterpage.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCHEDULEREGISTERPAGE_H
#define UI_SCHEDULEREGISTERPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ScheduleRegisterPage
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout_2;
    QLabel *titleLabel;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QListWidget *customerListWidget;
    QLabel *label;
    QTableWidget *appointmentTable;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QTimeEdit *timeEdit;
    QSpacerItem *verticalSpacer;
    QCalendarWidget *calendarWidget;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *addRVButton;
    QLabel *searchLabel;
    QVBoxLayout *verticalLayout;
    QLabel *appointmentLabel;
    QLabel *RVtimeLabel;
    QLineEdit *lineEdit;
    QPushButton *saveButton;
    QPushButton *loadButton;

    void setupUi(QWidget *ScheduleRegisterPage)
    {
        if (ScheduleRegisterPage->objectName().isEmpty())
            ScheduleRegisterPage->setObjectName("ScheduleRegisterPage");
        ScheduleRegisterPage->resize(1204, 600);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ScheduleRegisterPage->sizePolicy().hasHeightForWidth());
        ScheduleRegisterPage->setSizePolicy(sizePolicy);
        ScheduleRegisterPage->setMinimumSize(QSize(0, 600));
        verticalLayoutWidget = new QWidget(ScheduleRegisterPage);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(0, 0, 1201, 51));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        titleLabel = new QLabel(ScheduleRegisterPage);
        titleLabel->setObjectName("titleLabel");
        titleLabel->setGeometry(QRect(448, 10, 351, 29));
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(titleLabel->sizePolicy().hasHeightForWidth());
        titleLabel->setSizePolicy(sizePolicy1);
        QFont font;
        font.setPointSize(15);
        font.setBold(true);
        titleLabel->setFont(font);
        titleLabel->setLayoutDirection(Qt::LayoutDirection::RightToLeft);
        titleLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        layoutWidget = new QWidget(ScheduleRegisterPage);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(30, 70, 1141, 451));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        customerListWidget = new QListWidget(layoutWidget);
        customerListWidget->setObjectName("customerListWidget");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(customerListWidget->sizePolicy().hasHeightForWidth());
        customerListWidget->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(customerListWidget, 1, 7, 1, 2);

        label = new QLabel(layoutWidget);
        label->setObjectName("label");
        QFont font1;
        font1.setBold(true);
        label->setFont(font1);
        label->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(label, 0, 12, 1, 1);

        appointmentTable = new QTableWidget(layoutWidget);
        appointmentTable->setObjectName("appointmentTable");
        QSizePolicy sizePolicy3(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy3.setHorizontalStretch(1);
        sizePolicy3.setVerticalStretch(1);
        sizePolicy3.setHeightForWidth(appointmentTable->sizePolicy().hasHeightForWidth());
        appointmentTable->setSizePolicy(sizePolicy3);

        gridLayout->addWidget(appointmentTable, 1, 11, 1, 3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer, 3, 13, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 10, 1, 1);

        timeEdit = new QTimeEdit(layoutWidget);
        timeEdit->setObjectName("timeEdit");
        QSizePolicy sizePolicy4(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(timeEdit->sizePolicy().hasHeightForWidth());
        timeEdit->setSizePolicy(sizePolicy4);

        gridLayout->addWidget(timeEdit, 3, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout->addItem(verticalSpacer, 4, 3, 1, 1);

        calendarWidget = new QCalendarWidget(layoutWidget);
        calendarWidget->setObjectName("calendarWidget");
        QSizePolicy sizePolicy5(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Expanding);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(2);
        sizePolicy5.setHeightForWidth(calendarWidget->sizePolicy().hasHeightForWidth());
        calendarWidget->setSizePolicy(sizePolicy5);

        gridLayout->addWidget(calendarWidget, 0, 0, 2, 4);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 4, 12, 1, 1);

        addRVButton = new QPushButton(layoutWidget);
        addRVButton->setObjectName("addRVButton");
        sizePolicy4.setHeightForWidth(addRVButton->sizePolicy().hasHeightForWidth());
        addRVButton->setSizePolicy(sizePolicy4);

        gridLayout->addWidget(addRVButton, 3, 2, 1, 1);

        searchLabel = new QLabel(layoutWidget);
        searchLabel->setObjectName("searchLabel");
        searchLabel->setFont(font1);
        searchLabel->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        searchLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(searchLabel, 0, 7, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");

        gridLayout->addLayout(verticalLayout, 0, 4, 1, 1);

        appointmentLabel = new QLabel(layoutWidget);
        appointmentLabel->setObjectName("appointmentLabel");

        gridLayout->addWidget(appointmentLabel, 2, 3, 2, 6);

        RVtimeLabel = new QLabel(layoutWidget);
        RVtimeLabel->setObjectName("RVtimeLabel");

        gridLayout->addWidget(RVtimeLabel, 3, 0, 1, 1);

        lineEdit = new QLineEdit(layoutWidget);
        lineEdit->setObjectName("lineEdit");
        sizePolicy4.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy4);

        gridLayout->addWidget(lineEdit, 0, 8, 1, 1);

        saveButton = new QPushButton(layoutWidget);
        saveButton->setObjectName("saveButton");
        sizePolicy4.setHeightForWidth(saveButton->sizePolicy().hasHeightForWidth());
        saveButton->setSizePolicy(sizePolicy4);
        QFont font2;
        font2.setBold(false);
        saveButton->setFont(font2);
        saveButton->setLayoutDirection(Qt::LayoutDirection::RightToLeft);

        gridLayout->addWidget(saveButton, 4, 13, 1, 1);

        loadButton = new QPushButton(layoutWidget);
        loadButton->setObjectName("loadButton");
        sizePolicy4.setHeightForWidth(loadButton->sizePolicy().hasHeightForWidth());
        loadButton->setSizePolicy(sizePolicy4);
        loadButton->setLayoutDirection(Qt::LayoutDirection::RightToLeft);

        gridLayout->addWidget(loadButton, 4, 8, 1, 1);

        gridLayout->setRowStretch(0, 3);
        layoutWidget->raise();
        verticalLayoutWidget->raise();
        titleLabel->raise();

        retranslateUi(ScheduleRegisterPage);

        QMetaObject::connectSlotsByName(ScheduleRegisterPage);
    } // setupUi

    void retranslateUi(QWidget *ScheduleRegisterPage)
    {
        ScheduleRegisterPage->setWindowTitle(QCoreApplication::translate("ScheduleRegisterPage", "Widget", nullptr));
        titleLabel->setText(QCoreApplication::translate("ScheduleRegisterPage", "\354\204\234\353\271\204\354\212\244 \354\230\210\354\225\275 \352\264\200\353\246\254", nullptr));
        label->setText(QCoreApplication::translate("ScheduleRegisterPage", "\354\230\210\354\225\275 \355\230\204\355\231\251", nullptr));
        addRVButton->setText(QCoreApplication::translate("ScheduleRegisterPage", "\354\230\210\354\225\275", nullptr));
        searchLabel->setText(QCoreApplication::translate("ScheduleRegisterPage", "\352\262\200\354\203\211:", nullptr));
        appointmentLabel->setText(QCoreApplication::translate("ScheduleRegisterPage", "\355\231\225\354\240\225 \353\202\240\354\247\234 / \354\213\234\352\260\204", nullptr));
        RVtimeLabel->setText(QCoreApplication::translate("ScheduleRegisterPage", " \354\230\210\354\225\275 \354\213\234\352\260\204 :", nullptr));
        saveButton->setText(QCoreApplication::translate("ScheduleRegisterPage", "\354\240\200\354\236\245", nullptr));
        loadButton->setText(QCoreApplication::translate("ScheduleRegisterPage", "\353\266\210\353\237\254\354\230\244\352\270\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ScheduleRegisterPage: public Ui_ScheduleRegisterPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCHEDULEREGISTERPAGE_H
