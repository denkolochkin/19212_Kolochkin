#ifndef GAMEWIDGET_H
#define GAMEWIDGET_H

#include <QColor>
#include <QWidget>

class GameWidget : public QWidget {
    Q_OBJECT
public:
    explicit GameWidget(QWidget *parent = 0);
    ~GameWidget();

protected:
    void paintEvent(QPaintEvent *);
    void pressMouseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);

public slots:
    void clear(); // clear
    void setMainColor(const QColor &color); // set color of the cells

private slots:
    void paintGrid(QPainter &painter);
    void paintCanvas(QPainter &painter);

private:
    QColor mainColor;
    //bool* canvas; // map

    int canvasSize;
    std::vector<std::vector<bool>> canvas;
};

#endif // GAMEWIDGET_H
