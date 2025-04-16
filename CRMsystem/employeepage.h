#ifndef EMPLOYEEPAGE_H
#define EMPLOYEEPAGE_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QList>
#include <QMessageBox>
#include <QFile>
#include <QJsonObject>
#include <QVBoxLayout>
#include <QStackedLayout>

#include "customer.h"

class EmployeePage : public QWidget
{
    Q_OBJECT

public:
    explicit EmployeePage(QWidget *parent = nullptr);
    ~EmployeePage();

private slots:
    void addCustomer();
    void deleteCustomer();
    void handleEditButtonClicked();

private:
    void updateTable();
    void loadCustomersFromFile();
    void saveCustomersToFile();

    QVBoxLayout *mainLayout;
    QStackedLayout *stackedLayout;
    QLabel *emptyLabel;
    QLabel *countLabel;  // 고객 수 라벨
    QTableWidget *table;
    QPushButton *addButton;
    QPushButton *deleteButton;
    QPushButton *editButton;
    QLineEdit *companyEdit;
    QLineEdit *managerEdit;
    QLineEdit *phoneEdit;
    QLineEdit *addressEdit;
    QLineEdit *memoEdit;

    QList<Customer *> customerList;
    int editingRow = -1;
    const QString fileName = "customers.json";

private:
    QLineEdit *searchBar;
    void filterTable(const QString &keyword);
    // 상세 정보 다이얼로그 위한 함수
    void onTableItemDoubleClicked(QTableWidgetItem *item);

};

#endif // EMPLOYEEPAGE_H
