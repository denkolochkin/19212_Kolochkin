#pragma once

#include "game.h"

#include <QTimer>
#include <QMouseEvent>
#include <QPainter>
#include <QWidget>

class PainterWidget : public QWidget {
    Q_OBJECT

public:
    explicit PainterWidget(QWidget *parent = 0);
    ~PainterWidget(){};
    void setB(std::vector<int> b){ game->setB(b); };
    void setS(std::vector<int> s){ game->setS(s); };
    void setSizeX(size_t x);
    void setSizeY(size_t y);
    size_t getSizeX(){ return game->getCanvasSizeX(); };
    size_t getSizeY(){ return game->getCanvasSizeY();  };

public slots:
    void startGame() { timer->start(); };
    void stopGame() { timer->stop(); };
    void clear();
    void setMainColor(const QColor &color);
    void newGeneration();
    void paintGrid(QPainter &painter);
    void paintCanvas(QPainter &painter);
    void paintEvent(QPaintEvent *event);
    void pressMouseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void writeCanvas(std::string &s){ game->writeCanvas(s); };
    void writeRule(std::string &s){ game->writeRule(s); };
    void writeSizes(std::string &s){ game->writeSizes(s); };
    void getFile(const std::string &s){ game->processFile(s); };

private:
    GameWidget* game;
    QColor mainColor;
    QTimer* timer;
    size_t canvasSizeX;
    size_t canvasSizeY;
};
