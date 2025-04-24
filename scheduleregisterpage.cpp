#include "scheduleregisterpage.h"
#include <QMessageBox>
#include <QTextEdit>
#include <QJsonArray>
#include <QJsonDocument>
#include <QFile>
#include <QCheckBox>
#include <QToolButton>
#include "ui_scheduleregisterpage.h"
#include "editreservationdialog.h"

ScheduleRegisterPage::ScheduleRegisterPage(QWidget *parent)
    : QWidget(parent), ui(new Ui::ScheduleRegisterPage)
{
    ui->setupUi(this);

    //캘린더 버튼 수정 !!
    QToolButton *prevBtn = ui->calendarWidget->findChild<QToolButton*>("qt_calendar_prevmonth");
    QToolButton *nextBtn = ui->calendarWidget->findChild<QToolButton*>("qt_calendar_nextmonth");

    if (prevBtn) {
        prevBtn->setIcon(QIcon(":/icon/icon/left.png"));
        prevBtn->setIconSize(QSize(20, 20));
    }

    if (nextBtn) {
        nextBtn->setIcon(QIcon(":/icon/icon/right.png"));
        nextBtn->setIconSize(QSize(20, 20));
    }

    // 테마 색상 적용: 한화비전 주황색

    ui->calendarWidget->setStyleSheet(R"(
        /* 상단 네비게이션 바 스타일 */
        QCalendarWidget QWidget#qt_calendar_navigationbar {
            background-color: #ff6600;
        }

        /* 월/연도 버튼 */
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

        /* 날짜 셀 기본 및 선택 처리 */
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

    ui->customerListWidget->setStyleSheet(R"(
        QListWidget {
            background-color: white;
            border: 1px solid #ccc;
            font-size: 14px;
        }

        QListWidget::item {
            padding: 6px;
        }

        QListWidget::item:hover {
            background-color: #ffe0cc; /* 연한 주황 (hover) */
        }

        QListWidget::item:selected {
            background-color: #ff8533; /* 진한 주황 (selected) */
            color: white;
            font-weight: bold;
        }

    )");

    ui->appointmentTable->setStyleSheet(R"(
        QTableWidget {
            background-color: white;
            border: 1px solid #ccc;
            font-size: 14px;
        }

        QTableWidget::item {
            padding: 6px;
        }

        QTableWidget::item:hover {
            background-color: #ffe0cc; /* 연한 주황 (hover) */
        }

        QTableWidget::item:selected {
            background-color: #ff8533; /* 진한 주황 (selected) */
            color: white;
            font-weight: bold;
        }
    }
    )");

    //아이콘 추가
    ui->label->setTextFormat(Qt::RichText);
    ui->label->setText(
        "<img src=':/icon/icon/reservation.png' width='22' height='22' style='vertical-align: middle; margin-right: 8px;'>"
        "<span style='font-size: 15px; font-weight: bold; color: #333;'>예약 현황</span>"
        );

    ui->RVtimeLabel->setTextFormat(Qt::RichText);
    ui->RVtimeLabel->setText(
        "<img src=':/icon/icon/clock.png' width='16' height='16'style='vertical-align: middle; margin-right: 6px;'>"
        "<span style='font-size: 13px; color: #333;'>예약 시간</span>"
        );


    ui->saveButton->setStyleSheet("background-color: #ff6600; color: white;");

    // 기본 정렬 기준은 날짜 순서대로함.
    ui->appointmentTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents); // 날짜
    ui->appointmentTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents); // 시간

    ui->appointmentTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents); // 체크박스
    ui->appointmentTable->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch); // 상태


    connect(ui->loadButton, &QPushButton::clicked, this, &ScheduleRegisterPage::onLoadClicked);
    connect(ui->addRVButton, &QPushButton::clicked, this, &ScheduleRegisterPage::onAddReservationClicked);
    connect(ui->customerListWidget, &QListWidget::itemClicked, this, &ScheduleRegisterPage::onCustomerSelected);
    connect(ui->appointmentTable, &QTableWidget::cellDoubleClicked,
            this, &ScheduleRegisterPage::onAppointmentCellDoubleClicked);
    connect(ui->appointmentTable, &QTableWidget::cellChanged,
            this, &ScheduleRegisterPage::onAppointmentCellChanged);

    // static bool ascending = false;

    connect(ui->saveButton, &QPushButton::clicked, this, &ScheduleRegisterPage::onSaveClicked);

    connect(ui->lineEdit, &QLineEdit::textChanged, this, &ScheduleRegisterPage::onCustomerSearchTextChanged);

    onLoadClicked();
}

ScheduleRegisterPage::~ScheduleRegisterPage()
{
    delete ui;
}


void ScheduleRegisterPage::onCustomerSelected()
{
    QListWidgetItem *item = ui->customerListWidget->currentItem();
    if (!item) return;
    selectedCustomerId = item->data(Qt::UserRole).toString();
    refreshReservationTable(selectedCustomerId);

    QString company = item->text();
}

void ScheduleRegisterPage::onCustomerSearchTextChanged(const QString &text)
{
    for (int i = 0; i < ui->customerListWidget->count(); ++i) {
        QListWidgetItem *item = ui->customerListWidget->item(i);
        bool match = item->text().contains(text, Qt::CaseInsensitive);
        item->setHidden(!match);
    }
}

void ScheduleRegisterPage::onAddReservationClicked()
{
    if (selectedCustomerId.isEmpty()) {
        QMessageBox::warning(this, "오류", "고객을 선택해주세요.");
        return;
    }

    QDate date = ui->calendarWidget->selectedDate();
    QTime time = ui->timeEdit->time();

    int count = 0;
    for (const auto &list : std::as_const(reservationMap)) {
        for (const Reservation &r : list) {
            if (r.date == date && r.time == time) {
                ++count;
            }
        }
    }
    if (count >= 3) {
        QMessageBox::warning(this, "제한", "해당 시간 예약이 꽉 찼습니다.");
        return;
    }


    Reservation r;
    r.customerId = selectedCustomerId;
    r.date = date;
    r.time = time;

    reservationMap[selectedCustomerId].append(r);
    /////debug
    qDebug() << "[예약 추가됨] 고객 ID:" << selectedCustomerId
             << "날짜:" << r.date.toString("yyyy-MM-dd")
             << "시간:" << r.time.toString("HH:mm");
    qDebug() << "[총 예약 개수]" << reservationMap[selectedCustomerId].size();
    refreshReservationTable(selectedCustomerId);
    QMessageBox::information(this, "등록됨", "일정이 등록되었습니다.");

    QString formatted = QString("확정된 날짜: %1 / 시간: %2")
                            .arg(date.toString("yyyy-MM-dd"), time.toString("HH:mm"));
    ui->appointmentLabel->setText(formatted);  // QLineEdit 이름 확인 필요

}

bool ScheduleRegisterPage::hasReservationConflict(const QString &name, const QDate &date, const QTime &time)
{
    for (const auto &list : std::as_const(reservationMap)) {
        for (const Reservation &r : list) {
            if (r.date == date && r.time == time) {
                return true;
            }
        }
    }
    return false;
}


void ScheduleRegisterPage::refreshReservationTable(const QString &customerId)
{
    ui->appointmentTable->setSortingEnabled(false);  // 정렬 중단
    ui->appointmentTable->blockSignals(true);   //시그널 차단
    ui->appointmentTable->clearContents();  // 내용 비우기
    ui->appointmentTable->setColumnCount(5);
    ui->appointmentTable->setHorizontalHeaderLabels({"날짜", "시간", "메모", "완료","상태"});
////////////////////////////& 할지 말지 ...
    QList<Reservation> list = reservationMap[customerId];

    // 정렬 방향 따라 정렬
    // 리스트 직접 정렬!
    Qt::SortOrder order = ui->appointmentTable->horizontalHeader()->sortIndicatorOrder();
    // 항상 날짜 + 시간 기준 오름차순 정렬!
    std::sort(list.begin(), list.end(), [](const Reservation &a, const Reservation &b) {
        if (a.date != b.date)
            return a.date < b.date;
        return a.time < b.time;
    });

    ui->appointmentTable->setRowCount(list.size());

    for (int i = 0; i < list.size(); ++i) {
        const Reservation &r = list[i];
        ui->appointmentTable->setItem(i, 0, new QTableWidgetItem(r.date.toString("yyyy-MM-dd")));
        QTableWidgetItem *timeItem = new QTableWidgetItem(r.time.toString("HH:mm"));
        if (r.date == QDate::currentDate()) {
            timeItem->setForeground(QBrush(QColor("#ff6600")));  // 오늘이면 주황색
        }
        ui->appointmentTable->setItem(i, 1, timeItem);

        QString memo = "";
        for (const Customer &c : customers) {
            if (c.id() == customerId) {
                memo = c.memo();
                break;
            }
        }
        ui->appointmentTable->setItem(i, 2, new QTableWidgetItem(memo));  // 3번째열 - 메모 표시


        // 체크박스만 가운데 정렬된 셀 위젯
        QCheckBox *checkBox = new QCheckBox();
        checkBox->setChecked(r.status == ReservationStatus::Completed);

        QWidget *checkWidget = new QWidget();
        QHBoxLayout *layout = new QHBoxLayout(checkWidget);
        layout->addWidget(checkBox);
        layout->setAlignment(Qt::AlignCenter); // 가운데 정렬
        layout->setContentsMargins(0, 0, 0, 0); // 여백 제거

        checkWidget->setLayout(layout);
        ui->appointmentTable->setCellWidget(i, 3, checkWidget); //4번째 열에 삽입

        // 상태 텍스트
        QTableWidgetItem *statusItem = new QTableWidgetItem(statusToString(r.status));
        statusItem->setFlags(Qt::ItemIsEnabled);
        if (r.status == ReservationStatus::Completed) {
            statusItem->setForeground(Qt::red);
        }
        ui->appointmentTable->setItem(i, 4, statusItem);

        connect(checkBox, &QCheckBox::stateChanged, this, [=](int state) {
            for (Reservation &orig : reservationMap[selectedCustomerId]) {
                if (orig.id == r.id) {
                    orig.status = (state == Qt::Checked) ? ReservationStatus::Completed : ReservationStatus::Pending;
                    statusItem->setText(statusToString(orig.status));
                    statusItem->setForeground(orig.status == ReservationStatus::Completed ? Qt::red : Qt::black);
                    break;
                }
            }
        });
    }
    ui->appointmentTable->blockSignals(false);
    ui->appointmentTable->setSortingEnabled(true);  // 정렬 다시 활성화
    ui->appointmentTable->sortByColumn(0, Qt::AscendingOrder);

}


// Cell changed 상태 업데이트 추가
void ScheduleRegisterPage::onAppointmentCellChanged(int row, int column)
{
    if (column != 2 || selectedCustomerId.isEmpty()) return;
    if (row < 0 || row >= reservationMap[selectedCustomerId].size()) return;

    QTableWidgetItem *item = ui->appointmentTable->item(row, column);
    if (!item) return;

    Reservation &r = reservationMap[selectedCustomerId][row];
    r.status = item->checkState() == Qt::Checked ? ReservationStatus::Completed : ReservationStatus::Pending;

    // 상태 업데이트
    QTableWidgetItem *statusItem = ui->appointmentTable->item(row, 3);
    if (statusItem) {
        statusItem->setText(r.status == ReservationStatus::Completed ? "Completed" : "");
    }

    // 자동 저장
    onSaveClicked();
}



void ScheduleRegisterPage::onSaveClicked()
{
    QFile file("data.json");
    if (!file.open(QIODevice::WriteOnly)) return;

    QJsonArray customerArray;
    for (const Customer &c : customers) {
        customerArray.append(c.toJson());
    }

    QJsonArray reservationArray;
    for (const auto &list : std::as_const(reservationMap)) {
        for (const Reservation &r : list) {
            reservationArray.append(r.toJson());
        }
    }

    // customers.json에도 따로 저장 (직원 관리용)
    QFile customerFile("customers.json");
    if (customerFile.open(QIODevice::WriteOnly)) {
        QJsonDocument customerDoc(customerArray);
        customerFile.write(customerDoc.toJson());
        customerFile.close();
    }

    // data.json에는 고객 + 예약 통합 저장 (간트 차트 및 전체 통합용)
    QJsonObject root;
    root["customers"] = customerArray;
    root["reservations"] = reservationArray;

    QJsonDocument doc(root);
    file.write(doc.toJson());
    file.close();

    QMessageBox::information(this, "저장됨", "성공적으로 저장되었습니다.");
}


void ScheduleRegisterPage::onLoadClicked()
{
    QFile customerFile("customers.json");
    if (!customerFile.open(QIODevice::ReadOnly)) return;

    customers.clear();
    ui->customerListWidget->clear();

    QJsonDocument cdoc = QJsonDocument::fromJson(customerFile.readAll());
    customerFile.close();

    if (!cdoc.isArray()) return;

    QJsonArray customerArray = cdoc.array();
    for (const QJsonValue &val : customerArray) {
        Customer c = Customer::fromJson(val.toObject());
        customers.append(c);

        QListWidgetItem *item = new QListWidgetItem(c.company());
        item->setData(Qt::UserRole, c.id());
        ui->customerListWidget->addItem(item);
    }


    //  예약정보 불러오기  - table에 정보 뜨기
    QFile dataFile("data.json");
    if(!dataFile.open(QIODevice::ReadOnly)) return;

    reservationMap.clear();
    QJsonDocument ddoc=QJsonDocument::fromJson(dataFile.readAll());
    dataFile.close();

    QJsonObject root=ddoc.object();
    QJsonArray reservationArray=root["reservations"].toArray();

    for (const QJsonValue &val : reservationArray) {
        Reservation r = Reservation::fromJson(val.toObject());
        reservationMap[r.customerId].append(r);
    }
}

void ScheduleRegisterPage::editReservation(const QString &id, const QDate &newDate, const QTime &newTime) {
    for (auto &list : reservationMap) {
        for (Reservation &r : list) {
            if (r.id == id) {
                r.date = newDate;
                r.time = newTime;
                return;
            }
        }
    }
}


void ScheduleRegisterPage::onAppointmentCellDoubleClicked(int row, int column)
{
    if (selectedCustomerId.isEmpty()) return;

    Reservation &original = reservationMap[selectedCustomerId][row];
    EditReservationDialog dialog(original, this);



    if (dialog.exec() == QDialog::Accepted) {
        if (dialog.isDeleted()) {
            reservationMap[selectedCustomerId].removeAt(row);
        } else {
            Reservation updated = dialog.getUpdatedReservation();

            /////debug//////
            qDebug() << "[예약 수정 요청]";
            qDebug() << " └ 기존:" << original.date.toString("yyyy-MM-dd") << original.time.toString("HH:mm");
            qDebug() << " └ 수정후:" << updated.date.toString("yyyy-MM-dd") << updated.time.toString("HH:mm");


            int count = 0;
            for (const auto &list : std::as_const(reservationMap)) {
                for (const Reservation &r : list) {
                    if (r.date == updated.date && r.time == updated.time) {
                        ++count;
                    }
                }
            }
            // 자기 자신 포함한 상태로 이미 3개면 거부
            if (count >= 3 && (original.date != updated.date || original.time != updated.time)) {
                QMessageBox::warning(this, "제한", "해당 시간 예약이 꽉 찼습니다.");
                return;
            }

            // 충돌 없으면 반영
            reservationMap[selectedCustomerId][row] = updated;
        }

        refreshReservationTable(selectedCustomerId);
        onSaveClicked();  // 저장 파일에 반영
    }
}



void ScheduleRegisterPage::onCancelledClicked()
{
    this->close();
}
