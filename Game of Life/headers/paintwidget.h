#pragma once

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>


#define defaultColor "#000"

class paintWidget : public QWidget {
    Q_OBJECT

public:
    paintWidget();
    paintWidget(QWidget *parent);

private slots:
    void paintGrid(QPainter &painter);
    void paintCanvas(QPainter &painter);

private:
    //GameWidget* game;
    void paintEvent(QPaintEvent *);
    void setMainColor(const QColor &color);
    void pressMouseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    QColor mainColor;
    int canvasSize;
    int allSize;
   // void resetCanvas();
    std::vector<std::vector<bool>> canvas;
    std::vector<std::vector<bool>> nextCanvas;
};
