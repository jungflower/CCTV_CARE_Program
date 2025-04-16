#include "scheduleviewpage.h"
#include "ui_scheduleviewpage.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QGraphicsRectItem>
#include <QGraphicsSimpleTextItem>
#include <QBrush>
#include <QPen>
#include "reservationitem.h"

ScheduleViewPage::ScheduleViewPage(QWidget *parent)
    : QWidget(parent),
    ui(new Ui::ScheduleViewPage),
    scene(new QGraphicsScene(this))
{
    ui->setupUi(this);

    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    ui->graphicsView->setScene(scene);
    ui->dateEdit->setDate(QDate::currentDate());

    connect(ui->dateEdit, &QDateEdit::dateChanged, this, &ScheduleViewPage::onDateChanged);
    connect(ui->loadButton, &QPushButton::clicked, this, &ScheduleViewPage::onLoadClicked);
    loadFromFile();
    onDateChanged();
}

ScheduleViewPage::~ScheduleViewPage()
{
    delete ui;
}


void ScheduleViewPage::onLoadClicked()
{
    loadFromFile();        // 통합된 로딩 함수만 호출
    onDateChanged();
}

void ScheduleViewPage::loadFromFile()
{
    QFile file("data.json");
    if (!file.open(QIODevice::ReadOnly)) return;

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();

    QJsonObject root = doc.object();
    QJsonArray customerArray = root["customers"].toArray();
    QJsonArray reservationArray = root["reservations"].toArray();

    customers.clear();
    reservationMap.clear();

    for (const QJsonValue &val : customerArray) {
        Customer c = Customer::fromJson(val.toObject());
        customers.append(c);
    }

    for (const QJsonValue &val : reservationArray) {
        Reservation r = Reservation::fromJson(val.toObject());
        reservationMap[r.customerId].append(r);
    }
}


QString ScheduleViewPage::getCustomerNameById(const QString &id)
{
    for (const Customer &c : customers) {
        if (c.id() == id) return c.company();
    }
    return "Unknown";
}

void ScheduleViewPage::onDateChanged()
{
    QDate selectedDate = ui->dateEdit->date();
    drawGanttChart(selectedDate);
}

void ScheduleViewPage::resizeEvent(QResizeEvent *event)
{
    auto r=rect();
    auto h=r.height() - 607 + 450;
    auto g=ui->graphicsView->geometry();
    g.setHeight(h);
    ui->graphicsView->setGeometry(g);
    QWidget::resizeEvent(event);
}

void ScheduleViewPage::drawGanttChart(const QDate &date)
{
    scene->clear();

    const int hourStart = 0;
    const int hourEnd = 23;
    const int hourWidth = 50;
    const int blockHeight = 30;
    const int rowHeight = 40;
    const int labelWidth = 100;
    const int baseY = 40;

    // 1. 회사명 수집 및 정렬
    QSet<QString> companySet;
    for (const auto &pair : reservationMap) {
        for (const Reservation &r : pair) {
            if (r.date == date) {
                companySet.insert(getCustomerNameById(r.customerId));
            }
        }
    }

    QStringList companyList = companySet.values();
    std::sort(companyList.begin(), companyList.end());

    if (companyList.isEmpty()) {
        QGraphicsSimpleTextItem *emptyMsg = scene->addSimpleText("일정이 없습니다.");
        emptyMsg->setBrush(QBrush(QColor(150, 150, 150))); // 회색 텍스트
        emptyMsg->setFont(QFont("Arial", 14, QFont::Normal));
        emptyMsg->setPos(labelWidth + 100, baseY + 20);
        return; // 막대 지정필요없음ㅇㅇ
    }

    QMap<QString, int> companyToY;
    for (int i = 0; i < companyList.size(); ++i) {
        companyToY[companyList[i]] = baseY + i * rowHeight;
    }
    //-----색상 랜덤 지정---//
    QMap<QString, QColor> companyColors;
    QStringList colorPool = {
        "#FFBB3F","#FFA500","#FFD27F",
        "#FFB9B1","#FF8172",    //분홍계열
        "#FF8533", // 밝은 주황
    };

    for (int i = 0; i < companyList.size(); ++i) {
        companyColors[companyList[i]] = QColor(colorPool[i % colorPool.size()]);
    }

    // 2. 시간 라벨 (상단)
    for (int h = hourStart; h <= hourEnd; ++h) {
        int x = labelWidth + (h - hourStart) * hourWidth;
        QGraphicsSimpleTextItem *label = scene->addSimpleText(QString("%1:00").arg(h, 2, 10, QChar('0')));
        label->setPos(x + 5, baseY - 30);  // 위쪽 고정
    }


    // 회사명 라벨 (세로축)
    for (int i = 0; i < companyList.size(); ++i) {
        int y = baseY + i * rowHeight;
        companyToY[companyList[i]] = y;

        QGraphicsSimpleTextItem *label = scene->addSimpleText(companyList[i]);
        label->setPos(5, y + (blockHeight - 12) / 2); // 정중앙 정렬
    }


    // 4. 예약 막대 생성


    for (const auto &pair : reservationMap) {
        const QList<Reservation> &list = pair;
        for (const Reservation &r : list) {
            if (r.date != date) continue;

            QString company = getCustomerNameById(r.customerId);
            if (company.isEmpty()) continue;

            double startX = labelWidth + ((r.time.hour() - hourStart) + r.time.minute() / 60.0) * hourWidth;
            double rectWidth = 2.0 * hourWidth;  // 2시간 고정
            int y = companyToY[company];


            QColor color=companyColors.value(company);
            // 고객 정보 찾아오기 (팝업에 표시용)
            Customer matchedCustomer;
            for (const Customer &c : customers) {
                if (c.id() == r.customerId) {
                    matchedCustomer = c;
                    break;
                }
            }

            QRectF rect(startX, y, rectWidth, blockHeight);
            ReservationItem *item = new ReservationItem(r, matchedCustomer, rect);
            item->setBrush(QBrush(color));
            item->setPen(Qt::NoPen);
            scene->addItem(item);

        }
    }

    // 시간별 세로 라인 추가 (연한 회색)
    for (int h = hourStart; h <= hourEnd; ++h) {
        int x = labelWidth + (h - hourStart) * hourWidth;
        QGraphicsLineItem *line = scene->addLine(x, baseY - 20, x, baseY + companyList.size() * rowHeight,
                                                 QPen(QColor(200, 200, 200, 100))); // 연한 회색 + 투명도
        line->setZValue(-1);  // 가장 뒤로
    }

    // 5. 전체 보기 영역 설정
    int totalWidth = labelWidth + (hourEnd - hourStart + 1) * hourWidth + 300;
    int totalHeight = baseY + companyList.size() * rowHeight + 50;

    scene->setSceneRect(0, 0, totalWidth, totalHeight);
}

