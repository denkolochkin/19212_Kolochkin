#include "window.h"
#include "ui_window.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), currentColor(QColor("#000")), painter(new PainterWidget(this)) {
    ui->setupUi(this);
    connect(ui->btnStart, SIGNAL(clicked()), painter, SLOT(startGame()));
    connect(ui->btnClear, SIGNAL(clicked()), painter, SLOT(clear()));
    connect(ui->btnColor, SIGNAL(clicked()), this, SLOT(selectMasterColor()));
    connect(ui->btnClose, SIGNAL(clicked()), painter, SLOT(close()));
    connect(ui->btnRules, SIGNAL(clicked()), this, SLOT(selectRules()));
    connect(ui->btnSize, SIGNAL(clicked()), this, SLOT(selectSize()));
    ui->lytGame->addWidget(painter);
    canvasSizeX = painter->getSizeX();
    canvasSizeY = painter->getSizeY();
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::selectMasterColor() {
    QColor color = QColorDialog::getColor(currentColor, this, tr("Select color of figures"));
    painter->setMainColor(color);
}

void MainWindow::selectRules() {
    rules = new RulesDialog;
    B.clear();
    S.clear();
    rules->exec();
    if (!rules->B.empty() && !rules->S.empty()) {
        painter->setB(rules->B);
        painter->setS(rules->S);
    }
    if (rules->B.empty() && !rules->S.empty()) {
        QMessageBox::information(this, tr("Attention"), tr("Select B!"), QMessageBox::Ok);
        rules->exec();
    }
    if (rules->S.empty() && !rules->B.empty()) {
        QMessageBox::information(this, tr("Attention"), tr("Select S!"), QMessageBox::Ok);
        rules->exec();
    }
    if (rules->S.empty() && rules->B.empty()) {
        QMessageBox::information(this, tr("Attention"), tr("Select B and S!"), QMessageBox::Ok);
        rules->exec();
    }
}

void MainWindow::selectSize() {
    size = new SizeDialog;
    size->exec();
    if (size->x != 0 && size->y != 0) {
        painter->setSizeX(size->x);
        painter->setSizeY(size->y);
    }
    else if (size->x == 0 && size->y == 0) {
        QMessageBox::information(this, tr("Attention"), tr("Set X and Y!"), QMessageBox::Ok);
        size->exec();
    }
    else if (size->x == 0 && size->y != 0) {
        QMessageBox::information(this, tr("Attention"), tr("Set X!"), QMessageBox::Ok);
        size->exec();
    }
    else if (size->y == 0 && size->x != 0){
        QMessageBox::information(this, tr("Attention"), tr("Set Y!"), QMessageBox::Ok);
        size->exec();
    }
}

void MainWindow::on_btnSave_clicked() {
    std::string canvas;
    std::string rule;
    std::string sizes;
    painter->writeCanvas(canvas);
    painter->writeRule(rule);
    painter->writeSizes(sizes);
    painter->stopGame();
    QString name = QFileDialog::getSaveFileName(
        this, tr("Save game"), QDir::homePath(),
        tr("(*.rle)"));
    QFile file(name);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate))
        return;
    QString c = QString::fromStdString(canvas);
    QString r = QString::fromStdString(rule);
    QString s = QString::fromStdString(sizes);
    file.write(s.toUtf8());
    file.write("\t");
    file.write(r.toUtf8());
    file.write("\n");
    file.write(c.toUtf8());
}

void MainWindow::on_btnOpen_clicked() {
    painter->stopGame();
    QString name = QFileDialog::getOpenFileName(
        this, tr("Open game"), QDir::homePath(),
        tr("(*.rle)"));
    QFile file(name);
    if (!file.open(QIODevice::ReadOnly)) {
        painter->startGame();
        return;
    }
    QTextStream in(&file);
    QString str = in.readAll();
    painter->getFile(str.toStdString());
}
