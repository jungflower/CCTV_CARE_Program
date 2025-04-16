#include "employeepage.h"
#include "customer.h"
#include "customerdialog.h"  // 다이얼로그 헤더 포함
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QLabel>
#include <QFont>
#include <QGroupBox>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QIcon>
#include <QCryptographicHash>

EmployeePage::EmployeePage(QWidget *parent) : QWidget(parent) {
    // 색상 정의
    QString orangeColor = "#FF6600";
    QString backgroundColor = "#F9F9F9";
    QString textColor = "#555555";

    this->setStyleSheet("background-color: " + backgroundColor + ";");

    // 레이아웃 설정
    mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(20, 20, 20, 20);

    // 제목 라벨
    QLabel *titleLabel = new QLabel("CCTV 고객사 관리 시스템");
    QFont titleFont;
    titleFont.setPointSize(16);  // 혹은 setPixelSize(22); 원하는 크기로
    titleFont.setBold(true);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setFont(titleFont);
    titleLabel->setStyleSheet("color: black;");
    mainLayout->addWidget(titleLabel);

    // 버튼 생성
    addButton = new QPushButton("등록");
    editButton = new QPushButton("수정");
    deleteButton = new QPushButton("삭제");

    addButton->setIcon(QIcon(":/icon/icon/add.png"));
    editButton->setIcon(QIcon(":/icon/icon/edit.png"));
    deleteButton->setIcon(QIcon(":/icon/icon/delete.png"));

    // 아이콘 크기 지정 (선택)
    QSize iconSize(20, 20);  // 원하는 크기로 조절
    addButton->setIconSize(iconSize);
    editButton->setIconSize(iconSize);
    deleteButton->setIconSize(iconSize);
    //addButton->setStyleSheet("QPushButton { text-align: left; padding-left: 10px; }");

    // 세로 높이만 고정 (둥근 테두리 시각화)
    int widgetHeight = 35;
    addButton->setFixedHeight(widgetHeight);
    deleteButton->setFixedHeight(widgetHeight);
    editButton->setFixedHeight(widgetHeight);

    // 버튼 레이아웃
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(editButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->setAlignment(Qt::AlignRight);

    // 고객 아이콘 + 총 고객수 라벨 묶을 레이아웃
    QHBoxLayout *countLayout = new QHBoxLayout;

    // 고객 아이콘 (QLabel로 아이콘 표시)
    QLabel *customerIcon = new QLabel;
    customerIcon->setPixmap(QPixmap(":/icon/icon/total.png").scaled(28, 28, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    customerIcon->setFixedSize(28, 28);  // 약간 여유 공간 포함
    customerIcon->setAlignment(Qt::AlignVCenter | Qt::AlignLeft);

    // 총 고객수 라벨
    countLabel = new QLabel("총 고객 수: 0명");
    countLabel->setStyleSheet("color: #777777;");

    // 아이콘과 라벨을 countLayout에 추가
    countLayout->addWidget(customerIcon);
    countLayout->addWidget(countLabel);
    countLayout->setSpacing(3);  // 아이콘과 텍스트 사이 간격
    countLayout->setContentsMargins(0, 0, 0, 0);
    countLayout->setAlignment(Qt::AlignLeft);  // 왼쪽 정렬

    // 기존 headerLayout 사용해서 버튼들과 함께 배치
    QHBoxLayout *headerLayout = new QHBoxLayout;
    headerLayout->addLayout(countLayout);     // 왼쪽: 아이콘 + 라벨
    headerLayout->addLayout(buttonLayout);    // 오른쪽: 버튼들
    headerLayout->setStretch(0, 1);
    headerLayout->setStretch(1, 0);

    mainLayout->addLayout(headerLayout);

    // 검색 레이아웃
    QHBoxLayout *searchLayout = new QHBoxLayout;

    // 검색 아이콘 (QLabel)
    QLabel *searchIcon = new QLabel;
    searchIcon->setPixmap(QPixmap(":/icon/icon/search.png").scaled(20, 20, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    searchIcon->setFixedSize(24, 24);  // 여백 포함
    searchIcon->setAlignment(Qt::AlignCenter);

    // 검색 바
    searchBar = new QLineEdit;
    searchBar->setPlaceholderText("고객사명 또는 담당자명 검색...");
    searchBar->setClearButtonEnabled(true);
    searchBar->setStyleSheet(
        "QLineEdit {"
        "    background-color: white;"
        "    border: 1px solid #DDDDDD;"
        "    border-radius: 15px;"
        "    padding: 5px 15px;"
        "    color: #555555;"
        "}"
        );

    // 검색 레이아웃에 아이콘과 검색바 추가
    searchLayout->addWidget(searchIcon);
    searchLayout->addWidget(searchBar);
    searchLayout->setSpacing(10);  // 아이콘과 검색창 사이 여백
    searchLayout->setContentsMargins(0, 10, 0, 10);

    // 메인 레이아웃에 추가
    mainLayout->addLayout(searchLayout);

    this->setStyleSheet(
        "QLineEdit {"
        "    background-color: white;"
        "    border: 1px solid #DDDDDD;"
        "    border-radius: 15px;"
        "    padding: 5px 15px;"
        "    color: #555555;"
        "}"
        "QPushButton {"
        "    background-color: #FF6600;"
        "    color: white;"
        "    border: 1px solid #DDDDDD;"
        "    border-radius: 15px;"
        "    padding: 5px 20px;"
        //"    font-weight: bold;"
        "}"
        );

    // 등록된 고객 정보 없음 라벨
    emptyLabel = new QLabel("등록된 고객 정보가 없습니다.");
    emptyLabel->setAlignment(Qt::AlignCenter);
    emptyLabel->setStyleSheet("color: #999999;");

    // 테이블 생성
    table = new QTableWidget(0, 5);
    table->setStyleSheet(
        "QTableWidget {"
        " background-color: white;"
        " gridline-color: transparent;"  // 셀 경계선 감추기
        "  border: none;"
        "}"
        "QTableWidget::item {"
        " padding: 5px;"
        "  background-color: white;"       // 선택 안 했을 때 배경 흰색
        "  border: none;"
        "}"
        "QTableWidget::item:selected {"
        " background-color: #FF9900;"
        " color: black;"
        "}"
        "QHeaderView::section {"
        " background-color: #F0F0F0;"
        " padding: 5px;"
        " border: none;"
        " font-weight: bold;"
        "}"
        "QHeaderView::section:vertical {"
        "  background-color: white;"       // 행 번호 배경 흰색
        "  border: none;"
        "  padding: 5px;"
        "}"
        "QHeaderView::section:vertical:selected {"
        "  background-color: #FF8533;"     // 선택된 행 번호 강조 (실제 동작은 Qt 기본 스타일 영향 받음)"
        "}"
        "QTableView::item { border-bottom: 1px solid #dcdcdc;}"
        );
    QStringList headers = {"고객사명", "담당자명", "연락처", "주소", "메모"};
    table->setHorizontalHeaderLabels(headers);
    table->horizontalHeader()->setStretchLastSection(true);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setShowGrid(false);                   // 🔥 격자선 제거

    //mainLayout->addLayout(stackedLayout);

    stackedLayout = new QStackedLayout;
    stackedLayout->addWidget(emptyLabel);  // index 0
    stackedLayout->addWidget(table);       // index 1

    // 테이블 감쌀 프레임 추가
    QFrame *tableFrame = new QFrame;
    tableFrame->setStyleSheet(
        "QFrame {"
        "  border: 1px solid #DDDDDD;"
        "  border-radius: 15px;"
        "  background-color: white;"
        "}"
        );
    tableFrame->setContentsMargins(10, 10, 10, 10);  // 여백 제거

    QVBoxLayout *frameLayout = new QVBoxLayout(tableFrame);
    frameLayout->addLayout(stackedLayout);
    frameLayout->setContentsMargins(0, 0, 0, 0);  // 안쪽 여백도 없애기
    frameLayout->setSpacing(0);

    mainLayout->addWidget(tableFrame, 1);  // 아래쪽 공간을 자연스럽게 차지하도록

    // 시그널-슬롯
    connect(addButton, &QPushButton::clicked, this, &EmployeePage::addCustomer);
    connect(deleteButton, &QPushButton::clicked, this, &EmployeePage::deleteCustomer);
    connect(editButton, &QPushButton::clicked, this, &EmployeePage::handleEditButtonClicked);
    connect(searchBar, &QLineEdit::textChanged, this, &EmployeePage::filterTable);
    // 테이블 더블 클릭 시 처리
    connect(table, &QTableWidget::itemDoubleClicked, this, &EmployeePage::onTableItemDoubleClicked);
    // 데이터 로드
    loadCustomersFromFile();
}

EmployeePage::~EmployeePage() {
    saveCustomersToFile();
    qDeleteAll(customerList);
    customerList.clear();
}

void EmployeePage::addCustomer() {
    CustomerDialog dialog(this);
    dialog.setRegisterMode();

    while (true) {
        if (dialog.exec() != QDialog::Accepted)
            break;  // 취소 누른 경우

        QString companyName = dialog.companyName().trimmed();
        QString managerName = dialog.managerName().trimmed();
        QString phoneNumber = dialog.phoneNumber().trimmed();
        QString address = dialog.address().trimmed();
        QString memo = dialog.memo().trimmed();

        // 필수 입력값 확인
        if (companyName.isEmpty() || managerName.isEmpty() ||
            phoneNumber.isEmpty() || address.isEmpty()) {
            QMessageBox::warning(this, "입력 오류", "모든 필수 정보를 입력해주세요.");
            continue;  // 다시 입력창 띄움
        }

        // 중복 확인
        bool duplicate = false;
        for (Customer *existingCustomer : customerList) {
            if (existingCustomer->company() == companyName &&
                existingCustomer->manager() == managerName &&
                existingCustomer->phone() == phoneNumber) {
                QMessageBox::warning(this, "중복 오류", "이미 등록된 고객입니다.");
                duplicate = true;
                break;
            }
        }
        if (duplicate) continue;  // 다시 입력창 띄움

        Customer *customer = new Customer(companyName, managerName, phoneNumber, address, memo);

        // 이미지 저장 및 경로 설정
        QString sourcePath = dialog.imagePath();
        if (!sourcePath.isEmpty()) {
            QString savedPath = dialog.saveImageForCustomer(customer->id(),customer->company(),customer->manager(), sourcePath);
            if (!savedPath.isEmpty()) {
                customer->setImagePath(savedPath);
            }
        }
        ////////////////////////////
        customerList.append(customer);
        updateTable();
        saveCustomersToFile();
        QMessageBox::information(this, "등록 완료", "고객 정보가 성공적으로 등록되었습니다.");
        break;  // 등록 성공 → 루프 종료
    }
}

void EmployeePage::handleEditButtonClicked() {
    int row = table->currentRow();
    if (row < 0 || row >= customerList.size()) {
        QMessageBox::warning(this, "선택 오류", "수정할 항목을 먼저 선택하세요.");
        return;
    }

    Customer *customer = customerList.at(row);
    CustomerDialog dialog(this);
    dialog.setEditMode(customer->company(), customer->manager(),
                       customer->phone(), customer->address(), customer->memo(), customer->imagePath());

    while (true) {
        if (dialog.exec() != QDialog::Accepted)
            break;  // 취소한 경우

        QString companyName = dialog.companyName().trimmed();
        QString managerName = dialog.managerName().trimmed();
        QString phoneNumber = dialog.phoneNumber().trimmed();
        QString address = dialog.address().trimmed();
        QString memo = dialog.memo().trimmed();
        QString selectedImagePath = dialog.imagePath();

        // 필수 입력값 확인
        if (companyName.isEmpty() || managerName.isEmpty() ||
            phoneNumber.isEmpty() || address.isEmpty()) {
            QMessageBox::warning(this, "입력 오류", "모든 필수 정보를 입력해주세요.");
            continue;
        }

        if (companyName == customer->company() &&
            managerName == customer->manager() &&
            phoneNumber == customer->phone() &&
            address == customer->address() &&
            memo == customer->memo() &&
            selectedImagePath == customer->imagePath()) {
            QMessageBox::information(this, "수정 없음", "수정한 내용이 없습니다.");
            continue;
        }

        // 중복 확인 (자기 자신 제외)
        bool duplicate = false;
        for (int i = 0; i < customerList.size(); ++i) {
            if (i == row) continue;
            Customer *existing = customerList.at(i);
            if (existing->company() == companyName &&
                existing->manager() == managerName &&
                existing->phone() == phoneNumber) {
                QMessageBox::warning(this, "중복 오류", "이미 등록된 고객입니다.");
                duplicate = true;
                break;
            }
        }
        if (duplicate) continue;

        // 값 업데이트
        customer->setCompany(companyName);
        customer->setManager(managerName);
        customer->setPhone(phoneNumber);
        customer->setAddress(address);
        customer->setMemo(memo);

        // 이미지 경로가 변경되었을 경우 저장
        if (!selectedImagePath.isEmpty() && selectedImagePath != customer->imagePath()) {
            QString savedPath = dialog.saveImageForCustomer(customer->id(),customer->company(),customer->manager(), selectedImagePath);
            if (!savedPath.isEmpty()) {
                customer->setImagePath(savedPath);
            }
        }

        updateTable();
        saveCustomersToFile();
        QMessageBox::information(this, "수정 완료", "수정이 완료되었습니다.");
        break;
    }
}

void EmployeePage::deleteCustomer() {
    int row = table->currentRow();
    if (row < 0 || row >= customerList.size()) {
        QMessageBox::warning(this, "선택 오류", "삭제할 항목을 먼저 선택하세요.");
        return;
    }

    Customer *customer = customerList.at(row);
    QString message = QString("정말로 '%1' 고객 정보를 삭제하시겠습니까?").arg(customer->company());

    QMessageBox::StandardButton reply = QMessageBox::question(
        this, "삭제 확인", message,
        QMessageBox::Yes | QMessageBox::No
        );

    if (reply == QMessageBox::Yes) {
        customerList.removeAt(row);
        updateTable();
        saveCustomersToFile();
        QMessageBox::information(this, "삭제 완료", "고객 정보가 삭제되었습니다.");
    }
}

void EmployeePage::updateTable() {


    // 고객 목록이 비어있는 경우 메시지 표시
    if (customerList.isEmpty()) {
        stackedLayout->setCurrentIndex(0);  // emptyLabel
        countLabel->setText("총 고객 수: 0명");
        return;
    }

    stackedLayout->setCurrentIndex(1);  // table

    table->setRowCount(customerList.size());
    // 고객 목록이 비어있지 않으면 테이블에 고객 정보 추가
    for (int i = 0; i < customerList.size(); ++i) {
        Customer *customer = customerList.at(i);

        table->setItem(i, 0, new QTableWidgetItem(customer->company()));
        table->setItem(i, 1, new QTableWidgetItem(customer->manager()));
        table->setItem(i, 2, new QTableWidgetItem(customer->phone()));
        table->setItem(i, 3, new QTableWidgetItem(customer->address()));
        table->setItem(i, 4, new QTableWidgetItem(customer->memo()));

        // 고객 ID를 숨기고 setData에 저장 (UserRole 사용)
        table->item(i, 0)->setData(Qt::UserRole, customer->id());  // 고객 ID를 첫 번째 열에 숨겨서 저장
        qDebug() << "ID: " << table->item(i, 0)->data(Qt::UserRole).toString();
    }
    countLabel->setText(QString("총 고객 수: %1명").arg(customerList.size()));

}

void EmployeePage::loadCustomersFromFile() {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
        return;
    }

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    if (doc.isArray()) {
        QJsonArray array = doc.array();
        for (const QJsonValue &value : array) {
            QJsonObject obj = value.toObject();
            Customer *customer = new Customer(Customer::fromJson(obj));
            customerList.append(customer);
        }
    }

    file.close();
    updateTable();
}

void EmployeePage::saveCustomersToFile() {
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        return;
    }

    QJsonArray array;
    for (Customer *customer : customerList) {
        array.append(customer->toJson());
    }

    QJsonDocument doc(array);
    file.write(doc.toJson());
    file.close();
}

void EmployeePage::filterTable(const QString &keyword) {
    QString lowerKeyword = keyword.trimmed().toLower();

    for (int i = 0; i < table->rowCount(); ++i) {
        QString company = table->item(i, 0)->text().toLower();
        QString manager = table->item(i, 1)->text().toLower();

        bool match = company.contains(lowerKeyword) || manager.contains(lowerKeyword);
        table->setRowHidden(i, !match);
    }
}

void EmployeePage::onTableItemDoubleClicked(QTableWidgetItem *item) {
    // 더블 클릭한 행 번호
    int row = item->row();

    // 해당 행에서 고객 ID를 가져오기 (숨겨둔 데이터 사용)
    QString customerId = table->item(row, 0)->data(Qt::UserRole).toString();
    qDebug() << "customerId: " << customerId;

    // 고객 ID로 해당 고객 정보 검색
    Customer *customer = nullptr;
    for (Customer *cust : customerList) {
        if (cust->id() == customerId) {
            customer = cust;
            break;
        }
    }

    if (customer) {
        // CustomerDialog 열기
        CustomerDialog *dialog = new CustomerDialog(this);
        dialog->setCustomerInfo(customer);  // 고객 정보 설정
        dialog->exec();  // 다이얼로그 실행
    } else {
        // 고객을 찾을 수 없을 경우 처리
        QMessageBox::warning(this, "고객 찾기 실패", "해당 고객을 찾을 수 없습니다.");
    }
}



