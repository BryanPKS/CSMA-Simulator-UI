#include "mainwindow.h"
#include <QApplication>
#include <QHBoxLayout>
#include <QComboBox>
#include <QSlider>
#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QSpinBox>
#include <QDial>
#include <QRadioButton>
#include <QLCDNumber>

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>

//BryanKingSchilhab
//06/24/2022
//Assignment 3

int main(int argc, char *argv[])
{
    QApplication instance(argc, argv);
    MainWindow window;
    window.setWindowTitle("CSMA Simulator - Bryan King Schilhab");
    window.setStyleSheet("background-color: #D3D3D3");
    //window.setFixedSize(900,900);
    window.show();
    return instance.exec();
}

