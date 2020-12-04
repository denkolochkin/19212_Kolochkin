#include <QMessageBox>
#include <iostream>
#include <QTimer>
#include <QMouseEvent>
#include <QDebug>
#include <QRectF>
#include <QPainter>
#include <qmath.h>
#include<vector>
#include "game.h"

GameWidget::GameWidget(QWidget *parent) : QWidget(parent), canvasSize(50) {
    mainColor = "#000";
    //canvas = new bool[(canvasSize + 1) * (canvasSize + 1)];
    std::vector<std::vector<bool>> canvas(canvasSize + 1, std::vector<bool>(canvasSize + 1));
    //memset(canvas, false, sizeof(bool) * (canvasSize + 1) * (canvasSize + 1));
}

GameWidget::~GameWidget() {
    //delete [] canvas;
}

void GameWidget::clear() {
    for(int k = 1; k <= canvasSize; k++) {
        for(int j = 1; j <= canvasSize; j++) {
            canvas[k][j] = false;
        }
    }
    update();
}

void GameWidget::paintEvent(QPaintEvent *) {
    QPainter p(this);
    paintGrid(p);
    paintCanvas(p);
}

void GameWidget::pressMouseEvent(QMouseEvent* event) {
    double cellWidth = (double)width() / canvasSize;
    double cellHeight = (double)height() / canvasSize;
    int k = floor(event->y() / cellHeight) + 1;
    int j = floor(event->x() / cellWidth) + 1;
    canvas[k][j] = !canvas[k][j];
    update();
}

void GameWidget::mouseMoveEvent(QMouseEvent* event) {
    double cellWidth = (double)width() / canvasSize;
    double cellHeight = (double)height() / canvasSize;
    int k = floor(event->y() / cellHeight) + 1;
    int j = floor(event->x() / cellWidth) + 1;
    if(!canvas[k][j]) {
        canvas [k][j] = !canvas[k][j];
        update();
    }
}

void GameWidget::paintGrid(QPainter& painter) {
    QRect borders(0, 0, width() - 1, height() - 1);
    QColor gridColor = mainColor;
    gridColor.setAlpha(100);
    painter.setPen(gridColor);
    double cellWidth = (double)width() / canvasSize;
    for(double k = cellWidth; k <= width(); k += cellWidth) {
        painter.drawLine(k, 0, k, height());
    }
    double cellHeight = (double)height() / canvasSize;
    for(double k = cellHeight; k <= height(); k += cellHeight) {
        painter.drawLine(0, k, width(), k);
    }
    painter.drawRect(borders);
}

void GameWidget::paintCanvas(QPainter& painter) {
    double Width = (double)width() / canvasSize;
    double Height = (double)height() / canvasSize;
    std::cout<<canvas[1][1]<<std::endl;
    for(int k = 1; k <= canvasSize; k++) {
        for(int j = 1; j <= canvasSize; j++) {
            if(canvas[k][j] == true) {
                qreal left = (qreal)(Width * j - Width);
                qreal top  = (qreal)(Height * k - Height);
                QRectF rect(left, top, (qreal)Width, (qreal)Height);
                painter.fillRect(rect, QBrush(mainColor));
            }
        }
    }
}

void GameWidget::setMainColor(const QColor &color){
    mainColor = color;
    update();
}
