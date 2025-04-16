/********************************************************************************
** Form generated from reading UI file 'scheduleviewpage.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SCHEDULEVIEWPAGE_H
#define UI_SCHEDULEVIEWPAGE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ScheduleViewPage
{
public:
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QVBoxLayout *verticalLayout;
    QSpacerItem *horizontalSpacer_5;
    QGraphicsView *graphicsView;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_3;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer_9;
    QDateEdit *dateEdit;
    QPushButton *loadButton;

    void setupUi(QWidget *ScheduleViewPage)
    {
        if (ScheduleViewPage->objectName().isEmpty())
            ScheduleViewPage->setObjectName("ScheduleViewPage");
        ScheduleViewPage->resize(1200, 531);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ScheduleViewPage->sizePolicy().hasHeightForWidth());
        ScheduleViewPage->setSizePolicy(sizePolicy);
        ScheduleViewPage->setMinimumSize(QSize(1200, 530));
        layoutWidget = new QWidget(ScheduleViewPage);
        layoutWidget->setObjectName("layoutWidget");
        layoutWidget->setGeometry(QRect(20, 20, 1161, 491));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");

        gridLayout->addLayout(horizontalLayout_2, 2, 10, 1, 1);

        label = new QLabel(layoutWidget);
        label->setObjectName("label");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        QFont font;
        font.setPointSize(15);
        font.setBold(true);
        font.setStyleStrategy(QFont::PreferAntialias);
        font.setHintingPreference(QFont::PreferVerticalHinting);
        label->setFont(font);
        label->setFrameShape(QFrame::Shape::NoFrame);
        label->setTextFormat(Qt::TextFormat::PlainText);
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        gridLayout->addWidget(label, 0, 3, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        verticalLayout->addItem(horizontalSpacer_5);


        gridLayout->addLayout(verticalLayout, 0, 4, 1, 1);

        graphicsView = new QGraphicsView(layoutWidget);
        graphicsView->setObjectName("graphicsView");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy2);
        graphicsView->setLayoutDirection(Qt::LayoutDirection::RightToLeft);

        gridLayout->addWidget(graphicsView, 2, 1, 2, 9);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        verticalLayout_2->addItem(horizontalSpacer_2);


        gridLayout->addLayout(verticalLayout_2, 0, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 0, 9, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");

        gridLayout->addLayout(verticalLayout_3, 0, 6, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 0, 2, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(10, 20, QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);

        gridLayout->addItem(horizontalSpacer_9, 3, 0, 1, 1);

        dateEdit = new QDateEdit(layoutWidget);
        dateEdit->setObjectName("dateEdit");
        sizePolicy1.setHeightForWidth(dateEdit->sizePolicy().hasHeightForWidth());
        dateEdit->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(dateEdit, 1, 1, 1, 1);

        loadButton = new QPushButton(layoutWidget);
        loadButton->setObjectName("loadButton");
        sizePolicy1.setHeightForWidth(loadButton->sizePolicy().hasHeightForWidth());
        loadButton->setSizePolicy(sizePolicy1);
        loadButton->setLayoutDirection(Qt::LayoutDirection::RightToLeft);

        gridLayout->addWidget(loadButton, 1, 9, 1, 1);


        retranslateUi(ScheduleViewPage);

        QMetaObject::connectSlotsByName(ScheduleViewPage);
    } // setupUi

    void retranslateUi(QWidget *ScheduleViewPage)
    {
        ScheduleViewPage->setWindowTitle(QCoreApplication::translate("ScheduleViewPage", "Form", nullptr));
        label->setText(QCoreApplication::translate("ScheduleViewPage", "\354\235\274\354\240\225 \352\264\200\353\246\254", nullptr));
        loadButton->setText(QCoreApplication::translate("ScheduleViewPage", "\353\266\210\353\237\254\354\230\244\352\270\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ScheduleViewPage: public Ui_ScheduleViewPage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SCHEDULEVIEWPAGE_H
