#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QWidget>
#include <QPainter>
#include <QLCDNumber>
#include <fstream>
#include <QMenu>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QLCDNumber *num1;
    QLCDNumber *num2;
    QLCDNumber *num3;
    QLCDNumber *num4;
    QLCDNumber *num5;

public slots:
    void handleButton();
    void fileAction();
    void helpAction();
private:
    Ui::MainWindow *ui;
    QPushButton *startButton;
    int bins[20]= {0};
    QMenu *fileMenu;
    std::ifstream file;
    QPainter painter;
protected:
  void paintEvent(QPaintEvent *);


};
#endif // MAINWINDOW_H
