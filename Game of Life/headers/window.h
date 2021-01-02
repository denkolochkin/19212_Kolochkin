#pragma once

#include "painter.h"
#include "rulesdialog.h"
#include "sizedialog.h"

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void selectMasterColor();
    void selectRules();
    void selectSize();

private slots:
    void on_btnSave_clicked();
    void on_btnOpen_clicked();

private:
    Ui::MainWindow *ui;
    QColor currentColor;
    std::vector<int> B;
    std::vector<int> S;
    size_t x;
    size_t y;
    size_t canvasSizeX;
    size_t canvasSizeY;
    PainterWidget* painter;
    RulesDialog* rules;
    SizeDialog* size;
};
