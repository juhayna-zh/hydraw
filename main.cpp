#include "mainwindow.h"

#include <QApplication>
#include <QPixmap>
#include <QSplashScreen>
#include <QFontDatabase>
#include <QFont>
#include <QFile>
void setStyle(const QString &styleName)
{
    QFile file(QString("%1").arg(styleName));
    file.open(QFile::ReadOnly);
    QString css=QLatin1String(file.readAll());
    qApp->setStyleSheet(css);

}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPixmap openpix("openHyDraw.png");
    //openpix=openpix.scaled(705,400);
    setStyle("D:/QtApp/StyleSheet/HyStyle.css");
    QSplashScreen splash(openpix);
    splash.show();
    a.processEvents();
    MainWindow w;
    //w.setFont(QFont("微软雅黑"));
    w.show();
    splash.finish(&w);
    return a.exec();
}
