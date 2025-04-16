#include "customer.h"
#include <QJsonObject>
#include <QUuid>

Customer::Customer(){
    m_id=QUuid::createUuid().toString(QUuid::WithoutBraces);

}


Customer::Customer(const QString &company, const QString &manager, const QString &phone,
                   const QString &address, const QString &memo)
    : m_company(company), m_manager(manager), m_phone(phone), m_address(address), m_memo(memo)
{
    m_id=QUuid::createUuid().toString(QUuid::WithoutBraces);
}
// QString Customer::number() const { return m_number; }
QString Customer::id() const { return m_id; }
void Customer::setId(const QString &id) { m_id = id; }

QString Customer::company() const { return m_company; }
void Customer::setCompany(const QString &company) { m_company = company; }

QString Customer::manager() const { return m_manager; }
void Customer::setManager(const QString &manager) { m_manager = manager; }

QString Customer::phone() const { return m_phone; }
void Customer::setPhone(const QString &phone) { m_phone = phone; }

QString Customer::address() const { return m_address; }
void Customer::setAddress(const QString &address) { m_address = address; }

QString Customer::memo() const { return m_memo; }
void Customer::setMemo(const QString &memo) { m_memo = memo; }

// 이미지 추가부분
QString Customer::imagePath() const { return m_imagePath; }
void Customer::setImagePath(const QString &path) { m_imagePath = path; }
//

QJsonObject Customer::toJson() const
{
    QJsonObject json;

    json["id"]=m_id;
    json["company"] = m_company;
    json["manager"] = m_manager;
    json["phone"] = m_phone;
    json["address"] = m_address;
    json["memo"] = m_memo;
    // 이미지 경로 저장
    json["imagePath"] = m_imagePath;
    //
    return json;
}

Customer Customer::fromJson(const QJsonObject &json)
{
    Customer c(
        json["company"].toString(),
        json["manager"].toString(),
        json["phone"].toString(),
        json["address"].toString(),
        json["memo"].toString()
        );
    c.m_id=json["id"].toString();
    // 이미지 경로 불러오기
    c.setImagePath(json["imagePath"].toString());
    //
    return c;
}
