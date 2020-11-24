#include <QColor>
#include <QWidget>

class GameWidget : public QWidget {
    Q_OBJECT
public:
     GameWidget(QWidget *parent = 0);
    ~GameWidget();

public slots:
    void clear();
    void setCellsColor(const QColor &color);
    void selectGridColor(const QColor &color);

private:
    QColor cellsColor;
    QColor gridColor;
    bool* canvas;
    int canvasSize;
    void paintEvent(QPaintEvent *);
    void pressMouseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void makeGrid(QPainter &painter);
    void makeCanvas(QPainter &painter);
};
