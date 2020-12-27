#pragma once

#include "game.h"

#include <algorithm>
#include <QMessageBox>
#include <QTimer>
#include <QMouseEvent>
#include <QPainter>
#include <QWidget>

class PainterWidget : public QWidget {
    Q_OBJECT

public:
    explicit PainterWidget(QWidget *parent = 0);
    ~PainterWidget();
    void setB(std::vector<int> b);
    void setS(std::vector<int> s);
    void setSizeX(size_t x);
    void setSizeY(size_t y);
    size_t getSizeX();
    size_t getSizeY();

public slots:
    void startGame();
    void stopGame();
    void clear();
    void setMainColor(const QColor &color);
    void newGeneration();
    void paintGrid(QPainter &painter);
    void paintCanvas(QPainter &painter);
    void paintEvent(QPaintEvent *event);
    void pressMouseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void writeCanvas(std::string &s);
    void writeRule(std::string &s);
    void writeSizes(std::string &s);
    void getFile(const std::string &s);

private:
    GameWidget* game;
    QColor mainColor;
    QTimer* timer;
    size_t canvasSizeX;
    size_t canvasSizeY;
};
