#include "editreservationdialog.h"
#include <qcalendarwidget.h>
#include <QToolButton>
EditReservationDialog::EditReservationDialog(const Reservation &res, QWidget *parent)
    : QDialog(parent), original(res)
{
    setWindowTitle("예약 수정");
    QVBoxLayout *layout = new QVBoxLayout(this);

    dateEdit = new QDateEdit(res.date);
    dateEdit->setCalendarPopup(true);
    dateEdit->setDisplayFormat("yyyy-MM-dd");

    // 팝업 calendar에도 동일 스타일 적용
    QCalendarWidget* calendar = dateEdit->calendarWidget();
    // !!캘린더 버튼 수정 !!
    QToolButton *prevBtn = dateEdit->calendarWidget()->findChild<QToolButton*>("qt_calendar_prevmonth");
    QToolButton *nextBtn = dateEdit->calendarWidget()->findChild<QToolButton*>("qt_calendar_nextmonth");

    if (prevBtn) {
        prevBtn->setIcon(QIcon(":/icon/icon/left.png"));
        prevBtn->setIconSize(QSize(20, 20));
    }

    if (nextBtn) {
        nextBtn->setIcon(QIcon(":/icon/icon/right.png"));
        nextBtn->setIconSize(QSize(20, 20));
    }

    calendar->setStyleSheet(R"(
        QCalendarWidget QWidget#qt_calendar_navigationbar {
            background-color: #ff6600;
        }

        QCalendarWidget QToolButton {
            height: 30px;
            margin: 2px;
            padding: 2px 8px;
            color: white;
            background-color: #ff6600;
            font-weight: bold;
            border: none;
            border-radius: 10px;
        }

        QCalendarWidget QToolButton:hover {
            background-color: #ff8533;
        }

        QCalendarWidget QMenu {
            background-color: white;
        }

        QCalendarWidget QAbstractItemView {
            selection-background-color: transparent;
            outline: none;
        }

        QCalendarWidget QAbstractItemView::item:selected {
            background-color: #ff6600;
            border-radius: 15px;
            color: white;
        }

        QCalendarWidget QAbstractItemView::item:hover {
            background-color: #ffe0cc;
            border-radius: 15px;
        }
    )");

    timeEdit = new QTimeEdit(res.time);
    timeEdit->setDisplayFormat("HH:mm");

    layout->addWidget(new QLabel("날짜:"));
    layout->addWidget(dateEdit);
    layout->addWidget(new QLabel("시간:"));
    layout->addWidget(timeEdit);

    QHBoxLayout *btnLayout = new QHBoxLayout;
    deleteButton = new QPushButton("삭제");
    saveButton = new QPushButton("저장");
    btnLayout->addWidget(deleteButton);
    btnLayout->addWidget(saveButton);
    layout->addLayout(btnLayout);

    connect(deleteButton, &QPushButton::clicked, this, [&]() {
        deleted = true;
        accept();
    });
    connect(saveButton, &QPushButton::clicked, this, &QDialog::accept);
}

Reservation EditReservationDialog::getUpdatedReservation() const {
    Reservation updated = original;
    updated.date = dateEdit->date();
    updated.time = timeEdit->time();
    return updated;
}

bool EditReservationDialog::isDeleted() const {
    return deleted;
}
