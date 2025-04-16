/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCalendarWidget>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QPushButton *addCustomerButton;
    QPushButton *addReservationButton;
    QPushButton *saveButton;
    QPushButton *loadButton;
    QListWidget *customerListWidget;
    QLineEdit *nameEdit;
    QLineEdit *phoneEdit;
    QLineEdit *addressEdit;
    QLineEdit *memoEdit;
    QCalendarWidget *calendarWidget;
    QTimeEdit *timeEdit;
    QComboBox *statusComboBox;
    QTableWidget *reservationTable;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QScrollBar *verticalScrollBar;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName("Widget");
        Widget->resize(800, 600);
        addCustomerButton = new QPushButton(Widget);
        addCustomerButton->setObjectName("addCustomerButton");
        addCustomerButton->setGeometry(QRect(30, 30, 88, 26));
        addReservationButton = new QPushButton(Widget);
        addReservationButton->setObjectName("addReservationButton");
        addReservationButton->setGeometry(QRect(120, 30, 88, 26));
        saveButton = new QPushButton(Widget);
        saveButton->setObjectName("saveButton");
        saveButton->setGeometry(QRect(500, 120, 88, 26));
        loadButton = new QPushButton(Widget);
        loadButton->setObjectName("loadButton");
        loadButton->setGeometry(QRect(500, 160, 88, 26));
        customerListWidget = new QListWidget(Widget);
        customerListWidget->setObjectName("customerListWidget");
        customerListWidget->setGeometry(QRect(420, 220, 161, 211));
        nameEdit = new QLineEdit(Widget);
        nameEdit->setObjectName("nameEdit");
        nameEdit->setGeometry(QRect(90, 70, 141, 26));
        phoneEdit = new QLineEdit(Widget);
        phoneEdit->setObjectName("phoneEdit");
        phoneEdit->setGeometry(QRect(90, 100, 141, 26));
        addressEdit = new QLineEdit(Widget);
        addressEdit->setObjectName("addressEdit");
        addressEdit->setGeometry(QRect(320, 70, 151, 26));
        memoEdit = new QLineEdit(Widget);
        memoEdit->setObjectName("memoEdit");
        memoEdit->setGeometry(QRect(320, 100, 151, 26));
        calendarWidget = new QCalendarWidget(Widget);
        calendarWidget->setObjectName("calendarWidget");
        calendarWidget->setGeometry(QRect(20, 140, 371, 291));
        timeEdit = new QTimeEdit(Widget);
        timeEdit->setObjectName("timeEdit");
        timeEdit->setGeometry(QRect(110, 440, 118, 27));
        statusComboBox = new QComboBox(Widget);
        statusComboBox->setObjectName("statusComboBox");
        statusComboBox->setGeometry(QRect(20, 520, 86, 26));
        reservationTable = new QTableWidget(Widget);
        reservationTable->setObjectName("reservationTable");
        reservationTable->setGeometry(QRect(110, 511, 461, 41));
        label = new QLabel(Widget);
        label->setObjectName("label");
        label->setGeometry(QRect(30, 440, 71, 18));
        label_2 = new QLabel(Widget);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(40, 70, 66, 18));
        label_3 = new QLabel(Widget);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(40, 100, 66, 18));
        label_4 = new QLabel(Widget);
        label_4->setObjectName("label_4");
        label_4->setGeometry(QRect(250, 80, 66, 18));
        label_5 = new QLabel(Widget);
        label_5->setObjectName("label_5");
        label_5->setGeometry(QRect(250, 100, 66, 18));
        verticalScrollBar = new QScrollBar(Widget);
        verticalScrollBar->setObjectName("verticalScrollBar");
        verticalScrollBar->setGeometry(QRect(560, 220, 16, 211));
        verticalScrollBar->setOrientation(Qt::Orientation::Vertical);

        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QCoreApplication::translate("Widget", "Widget", nullptr));
        addCustomerButton->setText(QCoreApplication::translate("Widget", "add_CT", nullptr));
        addReservationButton->setText(QCoreApplication::translate("Widget", "add_RV", nullptr));
        saveButton->setText(QCoreApplication::translate("Widget", "save", nullptr));
        loadButton->setText(QCoreApplication::translate("Widget", "load", nullptr));
        label->setText(QCoreApplication::translate("Widget", " \354\230\210\354\225\275 \354\213\234\352\260\204 :", nullptr));
        label_2->setText(QCoreApplication::translate("Widget", "Name:", nullptr));
        label_3->setText(QCoreApplication::translate("Widget", "Phone:", nullptr));
        label_4->setText(QCoreApplication::translate("Widget", "Address:", nullptr));
        label_5->setText(QCoreApplication::translate("Widget", "Details:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
