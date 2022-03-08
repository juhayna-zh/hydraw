#ifndef TEXTGET_H
#define TEXTGET_H

#include <QDialog>
#include <QFont>
#include <QString>
class TextGet : public QDialog
{
    Q_OBJECT

public:
    TextGet(QWidget *parent = nullptr);
    void closeEvent(QCloseEvent*);
    ~TextGet();
signals:
    void have_got_text();
public slots:
    QString Text(){return txt;};
    QFont Font(){return  font;}
    void setFont(QFont f){font=f;}
private:
    QString txt;
    QFont font;
    bool ok;
    bool normalExit;
};
#endif // TEXTGET_H
