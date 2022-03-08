#ifndef DRAWWIDGET_H
#define DRAWWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QPixmap>
#include <QList>
class DrawWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DrawWidget(QWidget *parent = nullptr);
    void mousePressEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void mouseDoubleClickEvent(QMouseEvent*);
    void paintEvent(QPaintEvent*);
    void resizeEvent(QResizeEvent*);
    void wheelEvent(QWheelEvent*);
    enum GraphType{free,line,rectangle,ellipse,polygon,text};
    bool getFreeFlag();
signals:
    void widthChanged(int w);
    void invalidText();
public slots:
    void addPix(QPixmap);
    void undo();
    void clear();
    void save();
    void setStyle(int);
    void setWidth(int);
    void setColor(QColor);
    void setGraph(int);
    void setOnPaint(int);
    int getWidth(){return width;}
    void mouseClick();
    void chooseColor();
    void setTxtFont(QString t,QFont f){txt=t,font=f;}
    QString getTxt(){return txt;}
    void preTextGraph();
private:
    QPixmap *pix,*savePix;
    QPoint startPos;
    QPoint endPos;
    QPoint lastPos;
    int onPaint;
    int style;
    int width;
    QColor color;
    int graph;

    QTimer clickTimer;
    QList<QPixmap> cachePix;
    QString txt;
    QFont font;
    int now;
};

#endif // DRAWWIDGET_H
