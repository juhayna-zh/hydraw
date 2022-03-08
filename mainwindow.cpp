#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPalette>
#include <QToolBar>
#include <QToolButton>
#include <QGridLayout>
#include <QWheelEvent>
#include <windows.h>
#include <QButtonGroup>
#include <QAbstractButton>
#include <QShortcut>
#include <textget.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setMinimumSize(480,300);
    this->resize(880,550);
    QPixmap iconpix("iconHy.png");
    this->setWindowIcon(iconpix);
    this->setWindowTitle(tr("  HyDraw--宇宙第一酷的绘图软件！"));
    drawWidget=new DrawWidget(this);
    this->setCentralWidget(drawWidget);
    this->createToolBar();
    Sleep(100);
 //   QPixmap maskpix("mask1.png");
 //   maskpix=maskpix.scaled(this->size(),Qt::IgnoreAspectRatio);
  //  this->setMask(QBitmap(maskpix.mask()));
    //setAttribute(Qt::WA_TranslucentBackground);//背景透明，去除毛边
    QShortcut *keyZ = new QShortcut(this);
    keyZ->setKey(tr("ctrl+z"));keyZ->setAutoRepeat(false);
    connect(keyZ, SIGNAL(activated()), drawWidget, SLOT(undo()));
    QShortcut *keyS = new QShortcut(this);
    keyS->setKey(tr("ctrl+s"));keyS->setAutoRepeat(false);
    connect(keyS, SIGNAL(activated()), drawWidget, SLOT(save()));
    QShortcut *keyC = new QShortcut(this);
    keyC->setKey(tr("ctrl+c"));keyC->setAutoRepeat(false);
    connect(keyC, SIGNAL(activated()), drawWidget, SLOT(clear()));
}
void MainWindow::createToolBar()
{

    styleLabel=new QLabel("线型:");
    widthLabel=new QLabel("笔画大小:");
    colorsBtn=new QToolButton[10];
    styleCombo=new QComboBox;
    widthSpin=new QSpinBox;


    styleCombo->addItem(tr("隐线"),static_cast<int>(Qt::SolidLine));
    styleCombo->addItem(tr("实线"),static_cast<int>(Qt::DashLine));
    styleCombo->addItem(tr("虚线1(┆)"),static_cast<int>(Qt::DotLine));//┆ --
    styleCombo->addItem(tr("虚线2(:)"),static_cast<int>(Qt::DashDotLine));//··
    styleCombo->addItem(tr("虚线3(¡)"),static_cast<int>(Qt::DashDotDotLine));//﹎
    styleCombo->setCurrentIndex(1);
    drawWidget->setStyle(1);

    widthSpin->setValue(3);
    widthSpin->setSingleStep(2);
    widthSpin->setMinimum(1);
    widthSpin->setMaximum(100);
    QWidget *colorWidget=new QWidget(this);
    QGridLayout *colorLayout=new QGridLayout();
    colorWidget->setLayout(colorLayout);
    QPixmap pixmap(15,15);
    QColor cl[10]={Qt::black,Qt::red,QColor(255,165,0),Qt::yellow,Qt::gray,Qt::blue,Qt::magenta,Qt::green,Qt::cyan,Qt::white};
    drawWidget->setWidth(3);

    for(int i=0;i<10;i++)
    {
        pixmap.fill(cl[i]);
        colorsBtn[i].setIcon(QIcon(pixmap));
       // QPixmap pixmask("mask1.png");
       // pixmask=pixmask.scaled(colorsBtn[i].size());
        //colorsBtn[i].setMask(QBitmap(pixmask.mask()));
        colorLayout->addWidget(&colorsBtn[i],i/5,i%5);
    }
    curColorBtn=new QToolButton();
    drawWidget->setColor(Qt::black);
    pixmap=QPixmap(70,70);
    pixmap.fill(Qt::black);//这里的逻辑很重要，因为只是初始化，所以用黑色就行
   // curColorBtn->setAutoFillBackground(true);
   // curColorBtn->setPalette(QPalette(curColor));
    curColorBtn->setIcon(QIcon(pixmap));
   // QPixmap pixmask("mask2.png");
    curColorBtn->resize(30,30);
    //pixmask=pixmask.scaled(curColorBtn->size());
  //  curColorBtn->setMask(pixmask.mask());
    QLabel *space1=new QLabel();
    space1->setFixedWidth(20);
    QLabel *space2=new QLabel();
    space2->setFixedWidth(40);
    QLabel *space3=new QLabel(space1);
    QToolBar *toolBar=addToolBar("tool");
    toolBar->addWidget(styleLabel);
    toolBar->addWidget(space3);
    toolBar->addWidget(styleCombo);
    toolBar->addWidget(space1);
    toolBar->addWidget(widthLabel);
    toolBar->addWidget(widthSpin);
    toolBar->addWidget(space2);
    toolBar->addWidget(curColorBtn);
    toolBar->addWidget(colorWidget);
    drawWidget->setColor(Qt::white);
    QPalette toolpal(QColor(132,112,255,75));
    toolBar->setPalette(toolpal);
   // toolBar->setWindowOpacity(0.1);
    toolBar->setAutoFillBackground(true);
    drawWidget->setGraph(0);
   // this->setPalette(QPalette(QColor(132 112 255)));
    for(int i=0;i<10;i++)
    {
        connect(&colorsBtn[i],&QToolButton::clicked,[=](){
            QColor cl[10]={Qt::black,Qt::red,QColor(255,165,0),Qt::yellow,Qt::gray,Qt::blue,Qt::magenta,Qt::green,Qt::cyan,Qt::white};
            drawWidget->setColor(cl[i]);
            qDebug()<<i;
            QPixmap iconpix(70,70);
            iconpix.fill((cl[i]));
            curColorBtn->setIcon(QIcon(iconpix));
        });
    }
    connect(widthSpin,&QSpinBox::valueChanged,[=](){
        drawWidget->setWidth(widthSpin->value());
    });
    connect(styleCombo,SIGNAL(activated(int)),drawWidget,SLOT(setStyle(int)));
    connect(drawWidget,&DrawWidget::widthChanged,widthSpin,&QSpinBox::setValue);
    drawWidget->setColor(Qt::black);
    toolBar->addSeparator();
    QWidget *graphWidget=new QWidget;
    QGridLayout *graphLayout=new QGridLayout;
    graphWidget->setLayout(graphLayout);
    QString strGraph[6]={tr("自由"),tr("直线"),tr("矩形"),tr("圆"),tr("多边形"),tr("文字")};
    graphsBtn=new QToolButton[6];
    graphsBtnGrp=new QButtonGroup;
    for(int i=0;i<6;i++)
    {
        QPixmap graphicon(QString("graph%1.png").arg(i));
        QLabel *graphtext=new QLabel(strGraph[i]);
        graphtext->setAlignment(Qt::AlignCenter);
        graphsBtn[i].setIcon(QIcon(graphicon));
        graphsBtn[i].setFixedSize(50,30);
        graphLayout->addWidget(&graphsBtn[i],0,i,2,1);
        graphLayout->addWidget(graphtext,2,i,1,1);
        graphsBtnGrp->addButton(&graphsBtn[i],i);
    }
    graphsBtn[0].setDown(true);
    graphLayout->setHorizontalSpacing(10);
    toolBar->addWidget(graphWidget);
    drawWidget->setGraph(0);
    connect(graphsBtnGrp,SIGNAL(buttonClicked(QAbstractButton*)),this,SLOT(changePressedGraphBtn(QAbstractButton*)));

    connect(curColorBtn,&QToolButton::clicked,drawWidget,&DrawWidget::chooseColor);
    toolBar->addSeparator();
    undoBtn=new QToolButton;undoBtn->setIcon(QIcon("undo.png"));
    clearBtn=new QToolButton;clearBtn->setIcon(QIcon("clear.png"));
    saveBtn=new QToolButton;saveBtn->setIcon(QIcon("save.png"));
    QWidget *functionWidget=new QWidget;
    QGridLayout *functionLayout=new QGridLayout;
    functionWidget->setLayout(functionLayout);
    functionLayout->addWidget(undoBtn,0,0);
    functionLayout->addWidget(clearBtn,1,0);
    functionLayout->addWidget(saveBtn,2,0);
    toolBar->addWidget(functionWidget);
    connect(clearBtn,SIGNAL(clicked()),drawWidget,SLOT(clear()));
    connect(undoBtn,SIGNAL(clicked()),drawWidget,SLOT(undo()));
    connect(saveBtn,SIGNAL(clicked()),drawWidget,SLOT(save()));
    connect(drawWidget,&DrawWidget::invalidText,[=](){
        drawWidget->setGraph(0);
        graphsBtn[5].setDown(false);
        graphsBtn[0].setDown(true);
    });
    connect(&graphsBtn[5],&QToolButton::clicked,[=](){
        TextGet* textWidget=new TextGet;
        textWidget->show();
        connect(textWidget,&TextGet::have_got_text,[=](){
            drawWidget->setTxtFont(textWidget->Text(),textWidget->Font());
            drawWidget->preTextGraph();
        });
    });
}
void MainWindow::changePressedGraphBtn(QAbstractButton* b)
{
    for(int i=0;i<6;i++)
    {
        if(&graphsBtn[i]!=b) graphsBtn[i].setDown(false);
        else
        {
            graphsBtn[i].setDown(true);
            drawWidget->setGraph(i);
            qDebug()<<i;
        }
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}

