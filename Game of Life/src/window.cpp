#include <QTextStream>
#include <QFileDialog>
#include <QDebug>
#include <QColor>
#include <QColorDialog>
#include "window.h"
#include "ui_window.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), currentColor(QColor("#000")), game(new GameWidget(this)) {
    ui->setupUi(this);
    ui->lytGame->addWidget(game);
    connect(ui->btnClear, SIGNAL(clicked()), game, SLOT(clear()));
    connect(ui->btnColor, SIGNAL(clicked()), this, SLOT(selectCellsColor()));
    connect(ui->btnSize, SIGNAL(clicked()), this, SLOT(setSize()));
    connect(ui->btnCellsColor, SIGNAL(clicked()), this, SLOT(selectGridColor()));
    connect(ui->btnClose, SIGNAL(clicked()), game, SLOT(close()));
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::selectCellsColor() {
    QColor color = QColorDialog::getColor(currentColor, this, tr("Select color of "));
    currentColor = color;
    game->setCellsColor(color);
}

void MainWindow::selectGridColor() {
    QColor color = QColorDialog::getColor(gridColor, this, tr("Select"));
    gridColor = color;
    game->selectGridColor(color);
}
