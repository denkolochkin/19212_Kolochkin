#include <QMessageBox>
#include <QTimer>
#include <QMouseEvent>
#include <QDebug>
#include <QRectF>
#include <QPainter>
#include <qmath.h>
#include "game.h"

GameWidget::GameWidget(QWidget *parent) : QWidget(parent), canvasSize(10) {
    cellsColor = "#000";
    gridColor = "#000";
    gridColor.setAlpha(30);
    canvas = new bool[(canvasSize + 1) * (canvasSize + 1)];
    memset(canvas, 0, sizeof(bool) * (canvasSize + 1) * (canvasSize + 1));
}

GameWidget::~GameWidget() {
    delete [] canvas;
}

void GameWidget::clear() {
    for(int k = 1; k <= canvasSize; k++) {
        for(int j = 1; j <= canvasSize; j++) {
            canvas[k * canvasSize + j] = 0;
        }
    }
    if (gridColor != "#000") {
        gridColor = "#000";
        gridColor.setAlpha(30);
    }
    update();
}

void GameWidget::paintEvent(QPaintEvent *) {
    QPainter p(this);
    makeGrid(p);
    makeCanvas(p);
}

void GameWidget::pressMouseEvent(QMouseEvent* event) {
    double Width = (double)width() / canvasSize;
    double Height = (double)height() / canvasSize;
    int k = floor(event->y() / Height) + 1;
    int j = floor(event->x() / Width) + 1;
    canvas[k * canvasSize + j] = !canvas[k * canvasSize + j];
    update();
}

void GameWidget::mouseMoveEvent(QMouseEvent* event) {
    double Width = (double)width() / canvasSize;
    double Height = (double)height() / canvasSize;
    int i = floor(event->y() / Height) + 1;
    int j = floor(event->x() / Width) + 1;
    int location = i * canvasSize + j;
    if(canvas[location] == 0) {
        canvas[location] = 1;
        update();
    }
}

void GameWidget::makeGrid(QPainter& painter) {
    QRect borders(0, 0, width() - 1, height() - 1);
    painter.setPen(gridColor);
    gridColor.setAlpha(30);

    double Width = (double)width() / canvasSize;
    for(int i = Width; i <= width(); i += Width) {
        painter.drawLine(i, 0, i, height());
    }
    double Height = (double)height() / canvasSize;
    for(int i = Height; i <= height(); i += Height) {
        painter.drawLine(0, i, width(), i);
    }
    painter.drawRect(borders);
}

void GameWidget::makeCanvas(QPainter& painter) {
    double Width = (double)width() / canvasSize;
    double Height = (double)height() / canvasSize;
    for(int i = 1; i <= canvasSize; i++) {
        for(int j = 1; j <= canvasSize; j++) {
            if(canvas[i * canvasSize + j] == 1) {
                qreal left = (qreal)(Width * j - Width);
                qreal top  = (qreal)(Height * i - Height);
                QRectF rect(left, top, (qreal)Width, (qreal)Height);
                painter.fillRect(rect, QBrush(cellsColor));
            }
        }
    }
}

void GameWidget::setCellsColor(const QColor &color){
    cellsColor = color;
    update();
}

void GameWidget::selectGridColor(const QColor &color){
    gridColor = color;
    update();
}
