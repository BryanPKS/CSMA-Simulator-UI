#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QHBoxLayout>
#include <QComboBox>
#include <QSlider>
#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QPaintEvent>
#include <QPainter>
#include <QMenu>
#include <QMenuBar>
#include <QLineEdit>
#include <QGroupBox>
#include <QSpinBox>
#include <QDial>
#include <QRadioButton>
#include <QLCDNumber>
#include <QPushButton>
#include <QObject>
#include <QDockWidget>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <QFileDialog>
#include <QMessageBox>
int numVal[5];
int M, K, P, D, Tmax;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)

{
    std::ifstream file;
    QWidget *widget = new QWidget(this);
    widget->setAttribute(Qt::WA_NoSystemBackground);
    widget->setAttribute(Qt::WA_TranslucentBackground);
    widget->setFixedHeight(250);
    widget->setFixedWidth(250);
    setCentralWidget(widget);


    QMenuBar* menuBar = new QMenuBar();
    QMenu *fileMenu = new QMenu("File");
    QMenu *quitMenu = new QMenu("Quit");
    QMenu *helpMenu = new QMenu("Help");
    menuBar->addMenu(fileMenu);

    quitMenu->addAction("Stop  Execution");

    menuBar->addMenu(fileMenu);
    menuBar->addMenu(quitMenu);
    menuBar->addMenu(helpMenu);
    setMenuBar(menuBar);
    QAction *openAct = new QAction(tr("&Open"), this);
    QAction *aboutAct = new QAction(tr("&About"), this);
    fileMenu->addAction(openAct);
    helpMenu->addAction(aboutAct);


    startButton = new QPushButton("Start Simulation", widget);
    QPushButton *exitButton = new QPushButton("EXIT", widget);
    num1 = (new QLCDNumber);
    num1->setSegmentStyle(QLCDNumber::Flat);
    num1->setMode(QLCDNumber::Dec);
    num2 = new QLCDNumber(1);
    num2->setSegmentStyle(QLCDNumber::Flat);
    num2->setMode(QLCDNumber::Dec);
    num3 = new QLCDNumber;
    num3->setSegmentStyle(QLCDNumber::Flat);
    num3->setMode(QLCDNumber::Dec);
    num4 = new QLCDNumber;
    num4->setSegmentStyle(QLCDNumber::Flat);
    num4->setMode(QLCDNumber::Dec);
    num5 = new QLCDNumber;
    num5->setSegmentStyle(QLCDNumber::Flat);
    num5->setMode(QLCDNumber::Dec);
    num1->display(7);
    num2->display(1);
    num3->display(10);
    num4->display(0);
    num5->display(3000);

    QSpinBox *spinBox = new QSpinBox;
    spinBox->setSingleStep(2);
    spinBox->setRange(7, 99); // Cable length
    spinBox->setValue(5);

    QSlider *vSlider = new QSlider(Qt::Vertical);
    vSlider->setRange(1, 5); // Max message length of 5
    vSlider->setValue(1);

    QDial *dial = new QDial;
    dial->setRange(10,50); //10% to 50% chance to generate message
    dial->setNotchTarget(5);
    dial->setNotchesVisible(true);
    dial->setPageStep(20);

    QComboBox *comboBox = new QComboBox;
    comboBox->addItems({"0","1","2","3","4","5"}); // number of ticks for carrier sensing

    QSlider *slider = new QSlider(Qt::Horizontal);
    slider->setRange(3000, 5000); // We have >= 3000 ticks
    slider->setValue(3000);

    QObject::connect(spinBox, SIGNAL(valueChanged(int)), num1, SLOT(display(int)));
    QObject::connect(vSlider, SIGNAL(valueChanged(int)), num2, SLOT(display(int)));
    QObject::connect(dial, SIGNAL(valueChanged(int)), num3, SLOT(display(int)));
    QObject::connect(comboBox, SIGNAL(currentIndexChanged(int)), num4, SLOT(display(int)));
    QObject::connect(slider, SIGNAL(valueChanged(int)), num5, SLOT(display(int)));

    QObject::connect(exitButton, SIGNAL(clicked()), QApplication::instance(), SLOT(quit()));
    QObject::connect(startButton, SIGNAL(clicked()), this, SLOT(handleButton()));

    QObject::connect(openAct, SIGNAL(triggered()), this, SLOT(fileAction()));
    QObject::connect(aboutAct, SIGNAL(triggered()), this, SLOT(helpAction()));
    QObject::connect(quitMenu, &QMenu::triggered, [](QAction *action){
            QApplication::quit();
        });



    QDockWidget *num1Dock = new QDockWidget(tr("Carrier Length"), this);
    num1Dock->setAllowedAreas(Qt::LeftDockWidgetArea  );
    num1Dock->setWidget(num1);
    addDockWidget(Qt::LeftDockWidgetArea, num1Dock);
    num1Dock->setMinimumWidth(135);

    QDockWidget *spinDock = new QDockWidget(this);
    spinDock->setAllowedAreas(Qt::LeftDockWidgetArea  );
    spinDock->setWidget(spinBox);
    spinDock->setTitleBarWidget(new QWidget());
    addDockWidget(Qt::LeftDockWidgetArea, spinDock);
    spinDock->setMinimumWidth(135);

    QDockWidget *num2Dock = new QDockWidget(tr("Message Length"), this);
    num2Dock->setAllowedAreas(Qt::LeftDockWidgetArea  );
    num2Dock->setWidget(num2);
    addDockWidget(Qt::LeftDockWidgetArea, num2Dock);
    num2Dock->setMinimumWidth(135);

    QDockWidget *vSliderDock = new QDockWidget(this);
    vSliderDock->setAllowedAreas(Qt::LeftDockWidgetArea  );
    vSliderDock->setWidget(vSlider);
    vSliderDock->setTitleBarWidget(new QWidget());
    addDockWidget(Qt::LeftDockWidgetArea, vSliderDock);
    //vSlider->setMinimumWidth(135);


    QDockWidget *num4Dock = new QDockWidget(tr("Carrier Busy Delay"), this);
    num4Dock->setAllowedAreas(Qt::RightDockWidgetArea  );
    num4Dock->setWidget(num4);
    addDockWidget(Qt::RightDockWidgetArea, num4Dock);
    num4Dock->setMinimumWidth(145);

    QDockWidget *comboBoxDock = new QDockWidget(this);
    comboBoxDock->setAllowedAreas(Qt::RightDockWidgetArea  );
    comboBoxDock->setWidget(comboBox);
    comboBoxDock->setTitleBarWidget(new QWidget());
    addDockWidget(Qt::RightDockWidgetArea, comboBoxDock);
    comboBoxDock->setMinimumWidth(135);

    QDockWidget *num5Dock = new QDockWidget(tr("Tick Total"), this);
    num5Dock->setAllowedAreas(Qt::RightDockWidgetArea  );
    num5Dock->setWidget(num5);
    addDockWidget(Qt::RightDockWidgetArea, num5Dock);
    num5Dock->setMinimumWidth(135);

    QDockWidget *sliderDock = new QDockWidget(this);
    sliderDock->setAllowedAreas(Qt::RightDockWidgetArea  );
    sliderDock->setWidget(slider);
    sliderDock->setTitleBarWidget(new QWidget());
    addDockWidget(Qt::RightDockWidgetArea, sliderDock);
    sliderDock->setMinimumWidth(135);

    QDockWidget *startDock = new QDockWidget(this);
    startDock->setAllowedAreas(Qt::BottomDockWidgetArea  );
    startDock->setWidget(startButton);
    startDock->setTitleBarWidget(new QWidget());
    addDockWidget(Qt::BottomDockWidgetArea, startDock);
    startDock->setMinimumHeight(70);

    QDockWidget *num3Dock = new QDockWidget(tr("Probabilty %"), this);
    num3Dock->setAllowedAreas(Qt::BottomDockWidgetArea  );
    num3Dock->setWidget(num3);
    addDockWidget(Qt::BottomDockWidgetArea, num3Dock);
    num3Dock->setMinimumHeight(70);

    QDockWidget *dialDock = new QDockWidget(this);
    dialDock->setAllowedAreas(Qt::BottomDockWidgetArea  );
    dialDock->setWidget(dial);
    dialDock->setTitleBarWidget(new QWidget());
    addDockWidget(Qt::BottomDockWidgetArea, dialDock);
    dialDock->setMinimumHeight(70);

    QDockWidget *exitDock = new QDockWidget(this);
    exitDock->setAllowedAreas(Qt::BottomDockWidgetArea  );
    exitDock->setWidget(exitButton);
    exitDock->setTitleBarWidget(new QWidget());
    addDockWidget(Qt::BottomDockWidgetArea, exitDock);
    exitDock->setMinimumHeight(70);

}

void MainWindow::handleButton()
{
    M = num1->intValue();
    K = num2->intValue();
    P = num3->intValue();
    D = num4->intValue();
    Tmax = num5->intValue();

    std::ofstream file;
    file.open ("output.csv");
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    int j, T = 0;
     struct Station {
        int waitTimer = 0;
        bool waitBool = false;
        int state = 1; // 1 means idle, 2 means initiate message, 3 means sending message, 4 receiving message, 5 means wait
        int distanceToPacket;
        struct Packet;
    };

    struct Packet {
        bool active = false;
        int start;
        int destination;
        int startPos;
        int destinationPos;
        int messagelen;
        int position;
    };

    int wire[3] = {M, T, P}; // Array for wire, index 0 is length, 1 is ticks and 2 is p
    Station s[3]; // station 0 1 and 2
    s[0].distanceToPacket = 0;
    s[1].distanceToPacket = ((wire[0])/2)+1;
    s[2].distanceToPacket = wire[0];
    Packet carrier;
    carrier.messagelen = K;
    for( ; ; ) {
        for(int i = 0; i < 3; i++) {
            K = rand() % 100 + 1;
            if(K  < P && s[i].state == 1 && !carrier.active) {
                K = rand() % 3 + 1;
                    if(i == 0) { //these if statements decide where the station will send its message
                        j = rand() % 2 + 1;
                    }
                    if(i == 1) {
                        j = rand() % 2;
                        if(j == 1)
                            j = 2;
                    }
                    if(i == 2) {
                        j = rand() % 2;
                    }
                    s[i].state = 3;
                    s[j].state = 4;
                    carrier.active = true;
                    carrier.start = i;
                    carrier.destination = j;
                    carrier.startPos = s[i].distanceToPacket;
                    carrier.destinationPos = s[j].distanceToPacket;
                    carrier.position = s[i].distanceToPacket;
                    file << T << "," << i+1 << "," << j+1 << "," << K << "\n";
                }

            if(s[i].state == 3) {
                if(carrier.position == carrier.destinationPos) {
                    s[carrier.start].state = 1;
                    s[carrier.destination].state = 1;
                    carrier.active = false;
                }
                else if(carrier.position < carrier.destinationPos) {
                    carrier.position++;
                }
                else if(carrier.position > carrier.destinationPos)
                    carrier.position--;

            }

        }
        T++;
        if(T > Tmax) {
         break;
        }
    }
}

void MainWindow::paintEvent(QPaintEvent *)
{
    int x = 150,y = 250, binAmount = 20;

    QPainter painter(this);
    painter.setPen(Qt::black);
    painter.setFont(QFont("times",12));
    painter.drawText(150, 40, "The Histogram of GPDF001");
    painter.setBrush(QBrush(QColor(70,130,180), Qt::SolidPattern));

    for(int i = 0; i< binAmount-1;i++) {
        painter.drawRect(x,y,12,-(bins[i])*0.11);
       x += 12;
    }

    x=156;
    painter.setPen(QPen(QColor(255,99,71), 3));
    for(int i = 0; i< binAmount-2;i++) {
        painter.drawLine(x,(-bins[i]*0.11)+250,x+12,(-bins[i+1]*0.11)+250);
        x += 12;
    }

    painter.end();
    update();
}

void MainWindow::fileAction()
{
    QString qFileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", "CSV files (*.csv)");
    std::string fileName = qFileName.toStdString();
    file.open(fileName);
    if (file.is_open()) {
        int binAmount = 20 , input;
        float dataMin = 1, dataMax = 400;
        std::string line;
        float graphRange = dataMax - dataMin;
        float binRange = graphRange/binAmount;

        for(int k = 0; k < binAmount; k++) {
            while (file >> input) {
                dataMax = dataMin + binRange-1;

                if(input >= dataMin && input <= dataMax) {
                    bins[k]++;

                }

            }
            file.clear();
            file.seekg (0, std::ios::beg);
            dataMin += binRange;
        }
        file.close();
    }
}

void MainWindow::helpAction()
{
   QMessageBox::about(this, tr("About"),
            tr("Created by Bryan King Schilhab"));
}

MainWindow::~MainWindow()
{

}

