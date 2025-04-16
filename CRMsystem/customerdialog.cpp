#include "customerdialog.h"
#include <QFileDialog>
#include <QPixmap>
#include <QVBoxLayout>
#include <QLabel>
#include <QFormLayout>
#include <QPainter>
#include <QPainterPath>

CustomerDialog::CustomerDialog(QWidget *parent)
    : QDialog(parent), m_imagePath("")
{
    // 고객 정보 입력
    companyEdit = new QLineEdit(this);
    managerEdit = new QLineEdit(this);
    phoneEdit = new QLineEdit(this);
    addressEdit = new QLineEdit(this);
    memoEdit = new QLineEdit(this);

    QString lineEditStyle = R"(
        QLineEdit {
            border: 1px solid gray;
            border-radius: 10px;
            padding: 5px;
        }
    )";
    companyEdit->setStyleSheet(lineEditStyle);
    managerEdit->setStyleSheet(lineEditStyle);
    phoneEdit->setStyleSheet(lineEditStyle);
    addressEdit->setStyleSheet(lineEditStyle);
    memoEdit->setStyleSheet(lineEditStyle);

    // 버튼 등록 / 이미지 선택
    submitButton = new QPushButton("등록", this);
    selectImageButton = new QPushButton("이미지 선택", this);

    QString buttonStyle = R"(
    QPushButton {
        border: none;
        border-radius: 10px;
        padding: 8px 15px;
    }
    )";
    submitButton->setStyleSheet(buttonStyle);
    selectImageButton->setStyleSheet(buttonStyle);

    // 이미지 미리보기
    imageLabel = new QLabel(this);
    imageLabel->setFixedSize(120, 120);
    imageLabel->setAlignment(Qt::AlignCenter);
    imageLabel->setStyleSheet("border: none;");

    // 기본 원형 테두리 설정 (이미지 없음)
    QPixmap emptyPixmap(120, 120);
    emptyPixmap.fill(Qt::transparent);  // 투명한 배경을 채움
    imageLabel->setPixmap(createRoundedPixmap(emptyPixmap, 60));  // 기본 원형 테두리 그리기

    // 이미지 선택 관련 layout
    QVBoxLayout *imageLayout = new QVBoxLayout;
    imageLayout->addWidget(imageLabel, 0, Qt::AlignHCenter);
    imageLayout->addWidget(selectImageButton, 0, Qt::AlignHCenter);

    // 입력폼
    QFormLayout *formLayout = new QFormLayout;
    formLayout->addRow("고객사명", companyEdit);
    formLayout->addRow("담당자명", managerEdit);
    formLayout->addRow("연락처", phoneEdit);
    formLayout->addRow("주소", addressEdit);
    formLayout->addRow("메모", memoEdit);

    // 등록 버튼은 맨 아래 오른쪽 정렬
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addStretch();  // 왼쪽 여백
    buttonLayout->addWidget(submitButton);

    // 전체 수직 레이아웃
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(imageLayout);
    mainLayout->addLayout(formLayout);
    mainLayout->addLayout(buttonLayout);

    // // 배경 위젯 추가
    // QWidget *background = new QWidget(this);
    // background->setStyleSheet("background-color: #FAFAFA;");
    // background->setGeometry(this->rect());  // 다이얼로그 전체 크기로 설정
    // background->lower(); // 배경을 제일 아래로

    setLayout(mainLayout);

    //버튼 시그널
    connect(submitButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(selectImageButton, &QPushButton::clicked, this, &CustomerDialog::onSelectImage);

}

void CustomerDialog::setRegisterMode()
{
    setWindowTitle("고객 등록");
    // 등록 모드로 설정
    companyEdit->clear();
    managerEdit->clear();
    phoneEdit->clear();
    addressEdit->clear();
    memoEdit->clear();
    //imageLabel->clear();
    m_imagePath.clear();
}

void CustomerDialog::setEditMode(const QString &company, const QString &manager,
                                 const QString &phone, const QString &address, const QString &memo, const QString &imagePath)
{
    // 수정 모드로 설정
    companyEdit->setText(company);
    managerEdit->setText(manager);
    phoneEdit->setText(phone);
    addressEdit->setText(address);
    memoEdit->setText(memo);
    setImagePath(imagePath);  // 이미지 경로 설정
    setWindowTitle("고객 정보 수정");
    submitButton->setText("수정");
}

void CustomerDialog::setCustomerInfo(Customer* customer)
{
    if (!customer) return;

    setWindowTitle("고객 세부 사항");
    submitButton->setText("확인");
    selectImageButton->hide();

    // 필드에 고객 정보 채우기
    companyEdit->setText(customer->company());
    managerEdit->setText(customer->manager());
    phoneEdit->setText(customer->phone());
    addressEdit->setText(customer->address());
    memoEdit->setText(customer->memo());
    setImagePath(customer->imagePath());
}

QString CustomerDialog::companyName() const
{
    return companyEdit->text();
}

QString CustomerDialog::managerName() const
{
    return managerEdit->text();
}

QString CustomerDialog::phoneNumber() const
{
    return phoneEdit->text();
}

QString CustomerDialog::address() const
{
    return addressEdit->text();
}

QString CustomerDialog::memo() const
{
    return memoEdit->text();
}

QString CustomerDialog::imagePath() const
{
    return m_imagePath;  // 이미지 경로 반환
}

void CustomerDialog::setCompanyName(const QString &name)
{
    companyEdit->setText(name);
}

void CustomerDialog::setManagerName(const QString &name)
{
    managerEdit->setText(name);
}

void CustomerDialog::setPhoneNumber(const QString &phone)
{
    phoneEdit->setText(phone);
}

void CustomerDialog::setAddress(const QString &address)
{
    addressEdit->setText(address);
}

void CustomerDialog::setMemo(const QString &memo)
{
    memoEdit->setText(memo);
}

void CustomerDialog::onSelectImage()
{
    // 파일 다이얼로그 열기
    QString filePath = QFileDialog::getOpenFileName(this, "Select Customer Image", "", "Images (*.png *.jpg *.jpeg *.bmp)");
    if (!filePath.isEmpty()) {
        // 선택한 이미지를 미리보기로 표시
        QPixmap pixmap(filePath);
        QPixmap scaled = pixmap.scaled(120, 120, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        QPixmap rounded = createRoundedPixmap(scaled, 60);
        imageLabel->setPixmap(rounded);
        m_imagePath = filePath;  // 선택한 이미지 경로 저장
    }
}

void CustomerDialog::setImagePath(const QString &path)
{
    m_imagePath = path;
    if (!path.isEmpty()) {
        // 이미지 경로가 있다면 이미지 표시
        QPixmap pixmap(path);
        QPixmap scaled = pixmap.scaled(120, 120, Qt::KeepAspectRatio, Qt::SmoothTransformation);
        QPixmap rounded = createRoundedPixmap(scaled, 60);
        imageLabel->setPixmap(rounded);
    }
}

QString CustomerDialog::saveImageForCustomer(const QString &customerId, const QString &company, const QString &manager, const QString &sourceImagePath)
{
    QDir imageDir(QDir::currentPath() + "/images");
    if (!imageDir.exists()) {
        imageDir.mkpath(".");  // images 폴더 없으면 생성
    }

    QString imageSavePath = imageDir.filePath(company + "_" + manager + "_" + customerId + ".jpg");  // 고유 ID로 저장
    QPixmap pixmap(sourceImagePath);
    if (pixmap.save(imageSavePath)) {
        return imageSavePath;
    } else {
        return QString();  // 저장 실패 시 빈 문자열 반환
    }
}

QPixmap CustomerDialog::createRoundedPixmap(const QPixmap &src, int radius) {
    QPixmap dest(radius * 2, radius * 2);
    dest.fill(Qt::transparent);

    QPainter painter(&dest);
    painter.setRenderHint(QPainter::Antialiasing);

    // 이미지가 있을 경우, 이미지에 맞는 원형 그리기
    if (!src.isNull()) {
        QPainterPath path;
        path.addEllipse(0, 0, radius * 2, radius * 2); // 원형 path 추가
        painter.setClipPath(path);
        painter.drawPixmap(0, 0, radius * 2, radius * 2, src);
    }

    // 연한 회색 테두리 (이미지가 없더라도 테두리 그려줌)
    QPen pen(QColor("#B0B0B0"));  // 밝은 회색
    pen.setWidth(3);  // 두께 설정
    painter.setPen(pen);
    painter.setBrush(Qt::NoBrush);
    painter.drawEllipse(0, 0, radius * 2, radius * 2);  // 원형 테두리 그리기

    return dest;
}
