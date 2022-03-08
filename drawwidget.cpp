#include "drawwidget.h"
#include<QMouseEvent>
#include<QPaintEvent>
#include<QResizeEvent>
#include<QPen>
#include<QBrush>
#include<QPainter>
#include<windows.h>
#include<QColorDialog>
#include<QFileDialog>
#include<QFile>
#include<QIcon>
DrawWidget::DrawWidget(QWidget *parent) : QWidget(parent)
{
    setAutoFillBackground(true);
    setPalette(QPalette(Qt::white));
    pix=new QPixmap(size());
    savePix=new QPixmap();
    pix->fill(Qt::white);
    onPaint=0;
    setMinimumSize(600,400);
    connect(&clickTimer,SIGNAL(timeout()),this,SLOT(mouseClick()));
    now=0;
}
void DrawWidget::setStyle(int s)
{
    style=s;
}
void DrawWidget::setWidth(int w)
{
    width=w;
}
void DrawWidget::setColor(QColor c)
{
    color=c;
}
void DrawWidget::setGraph(int g)
{
    graph=g;
    onPaint=0;
}
void DrawWidget::setOnPaint(int flag)
{
    onPaint=flag;
}
void DrawWidget::mousePressEvent(QMouseEvent *event)
{
   // qDebug()<<"mousePressed";
    switch((GraphType)graph)
    {
    case free:
        addPix(*pix);
        startPos=event->pos();
        break;
    case line:
    {
        if(onPaint==0)
        {addPix(*pix);startPos=event->pos();onPaint=1;*savePix=QPixmap(*pix);}
    }
        break;
    case rectangle:
    {

        if(onPaint==0)
        {addPix(*pix);startPos=event->pos();onPaint=1;*savePix=QPixmap(*pix);}
    }
        break;
    case ellipse:
    {
        if(onPaint==0)
        {addPix(*pix);startPos=event->pos();onPaint=1;*savePix=QPixmap(*pix);}
    }
        break;
    case polygon:
    {
        if(onPaint==0)//初始状态
        {
            addPix(*pix);
            lastPos=startPos=event->pos();
            onPaint=1;
            *savePix=QPixmap(*pix);
            //this->setMouseTracking(true);
        }
        if(onPaint==1)
        {
            clickTimer.setSingleShot(true);
            clickTimer.start(300);
            *pix=QPixmap(*savePix);
            QPainter *painter=new QPainter;
            QPen pen(QBrush(color),width,(Qt::PenStyle)style);
            pen.setJoinStyle(Qt::RoundJoin);
            pen.setCapStyle(Qt::RoundCap);
            painter->begin(pix);
            painter->setPen(pen);
            painter->drawLine(lastPos,event->pos());
            painter->end();
            *savePix=QPixmap(*pix);
            endPos=event->pos();
            update();
        }
    }
        break;
    case text:
    {
        if(onPaint==1)
        {addPix(*pix);startPos=event->pos();onPaint=1;*savePix=QPixmap(*pix);}
    }
        break;
    default:
        break;
    }

}
void DrawWidget::mouseMoveEvent(QMouseEvent *e)
{
   // qDebug()<<"mouseMoving";
    clickTimer.stop();
    switch((GraphType)graph)
    {
    case free:
    {
        //qDebug()<<"on painting";
        if(getFreeFlag())
        {
            QPainter *painter=new QPainter;
            QPen pen(QBrush(color),width,(Qt::PenStyle)1);
            pen.setJoinStyle(Qt::RoundJoin);
            pen.setCapStyle(Qt::RoundCap);
            //pen.setColor(color);
            painter->begin(pix);
            painter->setPen(pen);
            qDebug()<<startPos<<" "<<e->pos();
            painter->drawLine(startPos,e->pos());
            painter->end();
            update();
        }
        startPos=e->pos();
        break;
    }
    case line:
    {
        if(onPaint>0)
        {
            *pix=QPixmap(*savePix);
            QPainter *painter=new QPainter;
            QPen pen(QBrush(QColor(color)),width,(Qt::PenStyle)2);
           // pen.setJoinStyle(Qt::RoundJoin);
           // pen.setCapStyle(Qt::RoundCap);
           // painter->begin(pix);
           // painter->setPen(pen);
            //qDebug()<<startPos<<" "<<e->pos();
           // painter->drawLine(startPos,e->pos());
           // pen=QPen(QBrush(color),width,(Qt::PenStyle)2);
            pen.setJoinStyle(Qt::RoundJoin);
            pen.setCapStyle(Qt::RoundCap);
            painter->begin(pix);
            painter->setPen(pen);
            painter->drawLine(startPos,e->pos());
            painter->end();
            endPos=e->pos();
            update();
        }
    }
        break;
    case rectangle:
    {
        if(onPaint>0)
        {
            *pix=QPixmap(*savePix);
            QPainter *painter=new QPainter;
            QPen pen(QBrush(color),width,(Qt::PenStyle)2);
            pen.setJoinStyle(Qt::RoundJoin);
            pen.setCapStyle(Qt::RoundCap);
            painter->begin(pix);
            painter->setPen(pen);
            qDebug()<<startPos<<" "<<e->pos();
            painter->drawRect(startPos.x(),startPos.y(),e->pos().x()-startPos.x(),e->pos().y()-startPos.y());
            painter->end();
            endPos=e->pos();
            update();
        }
    }
        break;
    case ellipse:
    {
        if(onPaint>0)
        {
            *pix=QPixmap(*savePix);
            QPainter *painter=new QPainter;
            QPen pen(QBrush(color),width,(Qt::PenStyle)2);
            pen.setJoinStyle(Qt::RoundJoin);
            pen.setCapStyle(Qt::RoundCap);
            painter->begin(pix);
            painter->setPen(pen);
            qDebug()<<startPos<<" "<<e->pos();
            painter->drawEllipse(startPos.x(),startPos.y(),e->pos().x()-startPos.x(),e->pos().y()-startPos.y());
            painter->end();
            endPos=e->pos();
            update();
        }
    }
        break;
    case polygon:
    {
        if(onPaint==1)
        {
            *pix=QPixmap(*savePix);
            QPainter *painter=new QPainter;
            QPen pen(QBrush(QColor(color)),width,(Qt::PenStyle)2);
            pen.setJoinStyle(Qt::RoundJoin);
            pen.setCapStyle(Qt::RoundCap);
            painter->begin(pix);
            painter->setPen(pen);
            painter->drawLine(lastPos,e->pos());
            painter->end();
            endPos=e->pos();
            onPaint=1;
            update();
        }
    }
        break;
    case text:
    {
        if(onPaint>0)
        {
            *pix=QPixmap(*savePix);
            QPainter *painter=new QPainter;
            QPen pen(QBrush(color),1,(Qt::PenStyle)2);
            pen.setJoinStyle(Qt::RoundJoin);
            pen.setCapStyle(Qt::RoundCap);
            painter->begin(pix);
            painter->setPen(pen);
            qDebug()<<startPos<<" "<<e->pos();
            painter->drawRect(startPos.x(),startPos.y(),e->pos().x()-startPos.x(),e->pos().y()-startPos.y());
            painter->end();
            endPos=e->pos();
            update();
        }
    }
        break;
    default:break;
    }
}
void DrawWidget::mouseReleaseEvent(QMouseEvent *e)
{
    switch((GraphType)graph)
    {
    case free:break;
    case line:
        if(onPaint>0)
        {
            *pix=QPixmap(*savePix);
            QPainter *painter=new QPainter;
            QPen pen(QBrush(color),width,(Qt::PenStyle)style);
            pen.setJoinStyle(Qt::RoundJoin);
            pen.setCapStyle(Qt::RoundCap);
            painter->begin(pix);
            painter->setPen(pen);
            painter->drawLine(startPos,endPos);
            painter->end();
            endPos=e->pos();
            update();
            onPaint=0;
        }
        break;
    case rectangle:
        if(onPaint>0)
        {
            *pix=QPixmap(*savePix);
            QPainter *painter=new QPainter;
            QPen pen(QBrush(color),width,(Qt::PenStyle)style);
            pen.setJoinStyle(Qt::RoundJoin);
            pen.setCapStyle(Qt::RoundCap);
            painter->begin(pix);
            painter->setPen(pen);
            painter->drawRect(startPos.x(),startPos.y(),e->pos().x()-startPos.x(),e->pos().y()-startPos.y());
            painter->end();
            endPos=e->pos();
            update();
            onPaint=0;
        }
        break;
    case ellipse:
        if(onPaint>0)
        {
            *pix=QPixmap(*savePix);
            QPainter *painter=new QPainter;
            QPen pen(QBrush(color),width,(Qt::PenStyle)style);
            pen.setJoinStyle(Qt::RoundJoin);
            pen.setCapStyle(Qt::RoundCap);
            painter->begin(pix);
            painter->setPen(pen);
            painter->drawEllipse(startPos.x(),startPos.y(),e->pos().x()-startPos.x(),e->pos().y()-startPos.y());
            painter->end();
            endPos=e->pos();
            update();
            onPaint=0;
        }
        break;
    case polygon:
        if(onPaint==1)
        {
            *pix=QPixmap(*savePix);
            QPainter *painter=new QPainter;
            QPen pen(QBrush(color),width,(Qt::PenStyle)style);
            pen.setJoinStyle(Qt::RoundJoin);
            pen.setCapStyle(Qt::RoundCap);
            painter->begin(pix);
            painter->setPen(pen);
            painter->drawLine(lastPos,endPos);
            painter->end();
            *savePix=QPixmap(*pix);
            lastPos=endPos=e->pos();
            update();
        }
        break;
    case text:
        if(onPaint>0)
        {
            *pix=QPixmap(*savePix);
            QPainter *painter=new QPainter;
            QPen pen(QBrush(color),width,(Qt::PenStyle)style);
            pen.setJoinStyle(Qt::RoundJoin);
            pen.setCapStyle(Qt::RoundCap);
            painter->begin(pix);
            painter->setPen(pen);
            font.setPixelSize(e->pos().y()-startPos.y());
            painter->setFont(font);
            painter->drawText(QPoint(startPos.x(),e->pos().y()),txt);
            painter->end();
            endPos=e->pos();
            update();
            onPaint=0;
            emit invalidText();
        }
        break;
    default:
        break;
    }
}
void DrawWidget::mouseDoubleClickEvent(QMouseEvent *e)
{
    clickTimer.stop();
    switch((GraphType)graph)
    {
    case polygon:
    {
        if(onPaint==1)
        {
            *pix=QPixmap(*savePix);
            QPainter *painter=new QPainter;
            QPen pen(QBrush(color),width,(Qt::PenStyle)style);
            pen.setJoinStyle(Qt::RoundJoin);
            pen.setCapStyle(Qt::RoundCap);
            painter->begin(pix);
            painter->setPen(pen);
            painter->drawLine(lastPos,e->pos());
            painter->drawLine(e->pos(),startPos);
            painter->end();
            lastPos=startPos;
            onPaint=0;
            update();
        }
    }
        break;
    default:
        break;
    }
}
void DrawWidget::mouseClick()
{
    switch((GraphType)graph)
    {
    case polygon:
    {
        if(onPaint==1)//连上一根线，重置lastPos
        {
            if((endPos-startPos).manhattanLength()<=10)
            {
                *pix=QPixmap(*savePix);
                QPainter *painter=new QPainter;
                QPen pen(QBrush(color),width,(Qt::PenStyle)style);
                pen.setJoinStyle(Qt::RoundJoin);
                pen.setCapStyle(Qt::RoundCap);
                painter->begin(pix);
                painter->setPen(pen);
                painter->drawLine(lastPos,startPos);
                painter->end();
                lastPos=startPos;
                onPaint=0;
                update();
                break;
            }
            *pix=QPixmap(*savePix);
            QPainter *painter=new QPainter;
            QPen pen(QBrush(color),width,(Qt::PenStyle)style);
            pen.setJoinStyle(Qt::RoundJoin);
            pen.setCapStyle(Qt::RoundCap);
            painter->begin(pix);
            painter->setPen(pen);
            painter->drawLine(lastPos,endPos);
            painter->end();
            lastPos=endPos;
            onPaint=1;
            update();

        }
    }
        break;
    default:
        break;
    }
}
void DrawWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(QPoint(0,0),*pix);
}
void DrawWidget::resizeEvent(QResizeEvent *e)
{
    if(height()>pix->height()||size().width()>pix->width())
    {
        QPixmap *newPix=new QPixmap(size());
        newPix->fill(Qt::white);
        QPainter p(newPix);
        p.drawPixmap(QPoint(0,0),*pix);
        pix=newPix;
    }
    QWidget::resizeEvent(e);
}
void DrawWidget::wheelEvent(QWheelEvent *e)
{
    if(e->angleDelta().y()>0)
    {
        if(width<=100) width+=1;
    }
    if(e->angleDelta().y()<0)
    {
        if(width>0) width-=1;
    }
    emit widthChanged(width);
}
void DrawWidget::chooseColor()
{
    QColor cl=QColorDialog::getColor(color,0,tr("选择任意颜色"));
    if(cl.isValid())
    {
        color=cl;
    }
}

void DrawWidget::clear()
{
    addPix(*pix);
    QPixmap *clearPix=new QPixmap(size());
    clearPix->fill(color);
    pix=clearPix;
    update();
}
void DrawWidget::addPix(QPixmap p)
{
    cachePix.append(p);
    if(cachePix.size()>10)
        cachePix.removeFirst();
    qDebug()<<"pix_size="<<cachePix.size();
}
void DrawWidget::undo()
{
    if(cachePix.size()>0)
    {
        *pix= QPixmap(cachePix.back());
        cachePix.removeLast();
        onPaint=0;
        update();
    }
}
void DrawWidget::save()
{
    QString filename=QFileDialog::getSaveFileName(0,tr("选择保存的文件位置"),"/","PNG格式图片(*.png);;JPG格式图片(*.jpg)");
    qDebug()<<filename;
    QFile file(filename);
    file.open(QIODevice::WriteOnly);
    if(filename=="") return;
    if(filename.at(filename.size()-2).toLower()=='n')
    {
    pix->save(&file, "PNG");
    }
    if(filename.at(filename.size()-2).toLower()=='p')
    {
    pix->save(&file, "JPG");
    }
}
bool DrawWidget::getFreeFlag()
{
    QString str[5]={"000000","111111","1111111100000000","11001100","111111110000110000"};
    if(now>=str[style].size()) now=0;
    //qDebug()<<str[style].at(now);
    return str[style].at(now++)=='1';
}
void DrawWidget::preTextGraph()
{
    if(txt=="")
    {
        qDebug()<<"txt==null";
        onPaint=0;
        graph=0;
        emit invalidText();
    }
    else
    {
        onPaint=1;
    }
}
