#include "painter.h"

#include <QMessageBox>

#define defaultColor "#000"

PainterWidget::PainterWidget(QWidget *parent) : QWidget(parent), 
                                                game(new GameWidget), 
                                                timer(new QTimer(this)) {
    mainColor = defaultColor;
    canvasSizeX = game->getCanvasSizeX();
    canvasSizeY = game->getCanvasSizeY();
    timer->setInterval(100);
    connect(timer, SIGNAL(timeout()), this, SLOT(newGeneration()));
}

void PainterWidget::newGeneration() {
    if(!game->newGeneration()) {
        QMessageBox::information(this, tr("The End"), 
                                 tr("Game finished."), QMessageBox::Ok);
        stopGame();
    }
    update();
}

void PainterWidget::clear() {
    game->clear();
    mainColor = defaultColor;
    update();
}

void PainterWidget::paintEvent(QPaintEvent *event) {
    QPainter p(this);
    paintGrid(p);
    paintCanvas(p);
}

void PainterWidget::pressMouseEvent(QMouseEvent* event) {
    game->mouseEvent((floor(event->y()/((double)height()/game->getCanvasSizeY()))), 
                     (floor(event->x()/((double)width()/game->getCanvasSizeX()))));
    update();
}

void PainterWidget::mouseMoveEvent(QMouseEvent* event) {
    size_t k = floor(event->y()/((double)height()/game->getCanvasSizeY()));
    size_t j = floor(event->x()/((double)width()/game->getCanvasSizeX()));
    if (k < game->getCanvasSizeY() && j < game->getCanvasSizeX() && k >= 0 && j >= 0) {
        game->moveEvent(k, j);
        update();
    }
}

void PainterWidget::paintGrid(QPainter& painter) {
    QRect borders(0, 0, width() - 1, height() - 1);
    QColor gridColor = mainColor;
    gridColor.setAlpha(100);
    painter.setPen(gridColor);
    double cellWidth = (double)width() / game->getCanvasSizeX();
    for(double k = cellWidth; k <= width(); k += cellWidth) {
        painter.drawLine(k, 0, k, height());
    }
    double cellHeight = (double)height() / game->getCanvasSizeY();
    for(double k = cellHeight; k <= height(); k += cellHeight) {
        painter.drawLine(0, k, width(), k);
    }
    painter.drawRect(borders);
}

void PainterWidget::paintCanvas(QPainter& painter) {
    double Width = (double)width() / game->getCanvasSizeX();
    double Height = (double)height() / game->getCanvasSizeY();
    for(size_t k = 0; k < game->getCanvasSizeY(); k++) {
        for(size_t j = 0; j < game->getCanvasSizeX(); j++) {
            if(game->checkCell(k, j)) {
                qreal left = (qreal)(Width * j);
                qreal top  = (qreal)(Height * k);
                QRectF rect(left, top, (qreal)Width, (qreal)Height);
                painter.fillRect(rect, QBrush(mainColor));
            }
        }
    }
}

void PainterWidget::setMainColor(const QColor &color){
    mainColor = color;
    update();
}

void PainterWidget::setSizeX(size_t x) {
    timer->stop();
    game->setSizeX(x);
    update();
}

void PainterWidget::setSizeY(size_t y) {
   timer->stop();
   game->setSizeY(y);
   update();
}
