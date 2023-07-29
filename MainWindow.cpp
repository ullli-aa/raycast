#include "MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent),
          comboBox(new QComboBox(this)) {
    resize(1120, 700);
    SetUpLight();
    this->setStyleSheet("background-color: black;");
    controller_.AddPolygon(Polygon({{-10,  -10},
                                    {1930, -10},
                                    {1930, 1090},
                                    {-10,  1090}}));

    setFocus();
    setMouseTracking(true);
    connect(comboBox, &QComboBox::currentTextChanged, [this]() {
        setFocus();
    });
}

void MainWindow::SetUpLight() {
    comboBox->addItem("polygons");
    comboBox->addItem("static-lights");
    comboBox->addItem("light");
    comboBox->setFixedSize(this->width(), 40);
    comboBox->setStyleSheet("background-color: white;");

}

void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter painter_(this);

    for (auto &polygon: controller_.GetPolygons()) {
        painter_.setPen({Qt::white, 2});
        for (int j = 1; j < polygon.getVertices().size(); ++j) {
            painter_.drawLine(polygon.getVertices()[j], polygon.getVertices()[j - 1]);
        }
        painter_.drawLine(polygon.getVertices()[polygon.getVertices().size() - 1], polygon.getVertices()[0]);
    }

    for (int i = 0; i < controller_.getStaticLights().size(); ++i) {
        controller_.SetLightSource(controller_.getStaticLights()[i]);

        controller_.CastRays();
        controller_.CreateLightArea();
        controller_.setLightArea(controller_.CreateLightArea());

        QPainterPath path;
        path.moveTo(controller_.getLightArea().getVertices()[controller_.getLightArea().getVertices().size() - 1]);
        for (int j = 0; j < controller_.getLightArea().getVertices().size(); ++j) {
            path.lineTo(controller_.getLightArea().getVertices()[j]);
        }

        QRadialGradient radialGrad(controller_.getStaticLights()[i], 400);
        radialGrad.setStops(QGradientStops({{0, QColor(50, 153, 206, 100)},
                                            {1, Qt::transparent}}));
        painter_.fillPath(path, radialGrad);
        path.clear();
    }

    if (this->comboBox->currentText() == "light") {
        QPainterPath path;
        for (int i = 0; i < controller_.getLightSources().size(); ++i) {
            controller_.SetLightSource(controller_.getLightSources()[i]);

            controller_.CastRays();
            controller_.CreateLightArea();
            controller_.setLightArea(controller_.CreateLightArea());

            path.moveTo(controller_.getLightArea().getVertices()[controller_.getLightArea().getVertices().size() - 1]);
            for (int j = 0; j < controller_.getLightArea().getVertices().size(); ++j) {
                path.lineTo(controller_.getLightArea().getVertices()[j]);
            }

            QRadialGradient radialGrad(controller_.getLightSources()[0], 350);
            radialGrad.setStops(QGradientStops({{0, QColor(50, 153, 206, 100)},
                                                {1, Qt::transparent}}));
            painter_.fillPath(path, radialGrad);
            path.clear();
            controller_.SetLightSource(controller_.getLightSources()[0]);

            painter_.setPen({Qt::white, 4});

            painter_.drawEllipse(controller_.getLightSources()[0], 2, 2);
        }
    }
}


void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    if (this->comboBox->currentText() == "light") {
        controller_.SetLightSource(event->pos());
        controller_.setLightSources(controller_.GetLightSource());
        for (int i = 0; i < controller_.getLightSources().size(); ++i) {
            controller_.SetLightSource(controller_.getLightSources()[i]);
            update();
        }
    }
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    if (this->comboBox->currentText() == "polygons") {
        controller_.SetLightSource(event->pos());
        if (event->buttons() == Qt::LeftButton) {
            if (count == 0) {
                controller_.AddPolygon(Polygon({controller_.GetLightSource()}));
                count = 1;
            } else {
                controller_.AddVertexToLastPolygon(controller_.GetLightSource());
            }
        } else if (event->buttons() == Qt::RightButton) {
            count = 0;
        }
    }

    if (this->comboBox->currentText() == "static-lights") {
        if (event->buttons() == Qt::LeftButton) {
            controller_.setStaticLights(event->pos());
        }
    }
    update();
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Escape) {
        close();
    }

    if (comboBox->currentText() == "polygons") {
        if ((event->key() == Qt::Key_Z) && (event->modifiers() & Qt::ControlModifier)) {
            if (controller_.GetPolygons().size() != 1) {
                controller_.deleteLastPolygon();
            }
            update();
        }
    }

    if (comboBox->currentText() == "static-lights") {
        if ((event->key() == Qt::Key_Z) && (event->modifiers() & Qt::ControlModifier)) {
            controller_.deleteLastStaticLight();
            update();
        }
    }
}
