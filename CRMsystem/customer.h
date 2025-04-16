#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QString>
#include <QJsonObject>

class Customer
{
public:
    Customer();
    Customer(const QString &company, const QString &manager, const QString &phone,
             const QString &address, const QString &memo);

    QString id() const;
    void setId(const QString &id);

    QString company() const;
    void setCompany(const QString &company);

    QString manager() const;
    void setManager(const QString &manager);

    QString phone() const;
    void setPhone(const QString &phone);

    QString address() const;
    void setAddress(const QString &address);

    QString memo() const;
    void setMemo(const QString &memo);

    QJsonObject toJson() const;
    static Customer fromJson(const QJsonObject &json);

    // 이미지 추가 부분
    QString imagePath() const;
    void setImagePath(const QString &path);
    //

private:
    QString m_id;
    QString m_company;
    QString m_manager;
    QString m_phone;
    QString m_address;
    QString m_memo;
    // image 추가 부분
    QString m_imagePath;
    //
};

#endif // CUSTOMER_H
