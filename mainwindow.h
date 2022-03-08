#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QComboBox>
#include <QSpinBox>
#include "drawwidget.h"
#include <QToolButton>
#include <QPushButton>
#include <QColor>
#include <QButtonGroup>
#include <QAbstractButton>
#include <QToolButton>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    //void wheelEvent(QWheelEvent*);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    DrawWidget *drawWidget;
    QLabel *styleLabel;
    QComboBox *styleCombo;
    QLabel *widthLabel;
    QSpinBox *widthSpin;
    QToolButton *curColorBtn;
    QToolButton *colorsBtn;
    QToolButton *graphsBtn;
    QButtonGroup *graphsBtnGrp;
    QToolButton *undoBtn;
    QToolButton *clearBtn;
    QToolButton *saveBtn;
    void createToolBar();
public slots:
    void changePressedGraphBtn(QAbstractButton*);
};
#endif // MAINWINDOW_H
