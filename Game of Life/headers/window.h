#include <QMainWindow>
#include <QColor>
#include "game.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void selectCellsColor();
    void selectGridColor();

private:
    Ui::MainWindow *ui;
    QColor currentColor;
    QColor gridColor;
    GameWidget* game;
};
