#include "textget.h"
#include <QTextEdit>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>
#include <QGridLayout>
TextGet::TextGet(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("输入你要填写的文字");
    setWindowIcon(QIcon("graph5.png"));
    this->setWindowModality(Qt::ApplicationModal);
    normalExit=false;
    QGridLayout *layout=new QGridLayout;
    setLayout(layout);
    QLabel *textLabel=new QLabel("文字:");
    QTextEdit *textEdit=new QTextEdit("示例文字ヽ(゜▽゜)ノ ");
    QLabel *fontLabel=new QLabel("字体:");
    QComboBox *fontCombo=new QComboBox;
    fontCombo->addItem("宋体");
    fontCombo->addItem("微软雅黑");
    fontCombo->addItem("楷体");
    fontCombo->addItem("隶书");
    fontCombo->addItem("黑体");
    QCheckBox *boldBtn=new QCheckBox(tr("加粗"));
    QCheckBox *italicBtn=new QCheckBox(tr("倾斜"));
    QPushButton *okBtn=new QPushButton("确定");
    QPushButton *cancelBtn=new QPushButton("取消");
    layout->addWidget(textLabel,0,0,1,1);
    layout->addWidget(textEdit,0,1,1,4);
    layout->addWidget(fontLabel,1,0,1,1);
    layout->addWidget(fontCombo,1,1,1,1);
    layout->addWidget(boldBtn,1,3,1,1);
    layout->addWidget(italicBtn,1,4,1,1);
    QWidget *w1=new QWidget;
    w1->setFixedSize(20,50);
   // QWidget *w2=new QWidget;
    layout->addWidget(w1,2,0);
    //layout->addWidget(w2,3,0);
    layout->addWidget(okBtn,3,3,1,1);
    layout->addWidget(cancelBtn,3,4,1,1);
    this->resize(400,300);
    font=QFont("宋体",15,15,false);
    textEdit->setFont(font);
    textLabel->setAlignment(Qt::AlignTop);
    textEdit->setFixedSize(350,100);
    txt="";
    ok=false;
    connect(fontCombo,&QComboBox::activated,[=](){
        font.setFamily(fontCombo->currentText());
        textEdit->setFont(font);
        this->setFont(font);
    });
    connect(boldBtn,&QCheckBox::stateChanged,[=](){
        font.setBold(boldBtn->checkState());
        textEdit->setFont(font);
        this->setFont(font);
    });
    connect(italicBtn,&QCheckBox::stateChanged,[=](){
        font.setItalic(italicBtn->checkState());
        textEdit->setFont(font);
        this->setFont(font);
    });
    connect(okBtn,&QPushButton::clicked,[=](){
        this->ok=true;
        this->txt=textEdit->toPlainText();
        qDebug()<<font<<txt;
        this->normalExit=true;
        this->close();
        emit have_got_text();
    });
    connect(cancelBtn,&QPushButton::clicked,[=](){
        qDebug()<<font;
        this->txt="";
        this->ok=true;
        this->normalExit=true;
        this->close();
        emit have_got_text();
    });
}
void TextGet::closeEvent(QCloseEvent *)
{
    qDebug()<<"Widget Closed";
    if(normalExit==false)
        txt="";
}
TextGet::~TextGet()
{
}

