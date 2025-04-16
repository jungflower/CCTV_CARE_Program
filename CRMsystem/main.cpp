#include "widget.h"

#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 폰트 등록
    int fontId = QFontDatabase::addApplicationFont(":/fonts/fonts/NanumSquareNeo-bRg.ttf");

    if (fontId != -1) {
        qDebug() << "apply font";
        QString fontFamily = QFontDatabase::applicationFontFamilies(fontId).at(0);
        QFont appFont(fontFamily);
        appFont.setPixelSize(13);  // 폰트 크기 설정
        appFont.setStyleStrategy(QFont::PreferAntialias); // 안티앨리어싱 적용
        a.setFont(appFont);
        qDebug() << "Font applied successfully.";
    } else {
        qDebug() << "Failed to load font.";
    }


    Widget w;
    w.show();
    return a.exec();
}
