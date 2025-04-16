#ifndef CUSTOMERDIALOG_H
#define CUSTOMERDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QPixmap>
#include "customer.h"

class CustomerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CustomerDialog(QWidget *parent = nullptr);

    // 모드 설정 함수
    void setRegisterMode();
    void setEditMode(const QString &company, const QString &manager,
                     const QString &phone, const QString &address, const QString &memo, const QString &imagePath);
    void setCustomerInfo(Customer* customer);

    // Getter 함수들
    QString companyName() const;
    QString managerName() const;
    QString phoneNumber() const;
    QString address() const;
    QString memo() const;
    QString imagePath() const; // 이미지 경로 반환 함수

    // Setter 함수들
    void setCompanyName(const QString &name);
    void setManagerName(const QString &name);
    void setPhoneNumber(const QString &phone);
    void setAddress(const QString &address);
    void setMemo(const QString &memo);
    void setImagePath(const QString &path); // 이미지 경로 설정 함수
    QString saveImageForCustomer(const QString &customerId, const QString &company, const QString &manager, const QString &sourceImagePath); // 이미지 저장 함수
    QPixmap createRoundedPixmap(const QPixmap &src, int radius);
private slots:
    void onSelectImage(); // 이미지 선택 함수

private:
    QLineEdit *companyEdit;
    QLineEdit *managerEdit;
    QLineEdit *phoneEdit;
    QLineEdit *addressEdit;
    QLineEdit *memoEdit;
    QPushButton *submitButton;
    QPushButton *selectImageButton;  // 이미지 선택 버튼
    QLabel *imageLabel;              // 이미지 미리보기 레이블

    QString m_imagePath;  // 이미지 파일 경로 저장
};

#endif // CUSTOMERDIALOG_H
