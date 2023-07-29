#pragma once

#include <QMainWindow>
#include "Ray.h"
#include "Polygon.h"
#include "Controller.h"
#include "QWidget"
#include "QComboBox"
#include "QPaintEvent"
#include "QMouseEvent"
#include "QKeyEvent"
#include <QPainter>
#include "QPainterPath"
#include "QLinearGradient"

class MainWindow : public QMainWindow {
Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);

    void SetUpLight();

    void paintEvent(QPaintEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

    void keyPressEvent(QKeyEvent *event) override;

private:
    Controller controller_;
    QWidget draw;
    QComboBox *comboBox;
    int count = 0;
};
