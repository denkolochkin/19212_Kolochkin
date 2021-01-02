#include "sizedialog.h"
#include "ui_sizedialog.h"

SizeDialog::SizeDialog(QWidget *parent) : QDialog(parent), 
                       x(0), y(0), ui(new Ui::SizeDialog) {
    ui->setupUi(this);
}

SizeDialog::~SizeDialog() {
    delete ui;
}

void SizeDialog::on_spinBoxSizeX_valueChanged(int arg1) {
    x = arg1;
}

void SizeDialog::on_spinBoxSizeY_valueChanged(int arg1) {
    y = arg1;
}

void SizeDialog::on_btnOK_clicked() {
    close();
}
