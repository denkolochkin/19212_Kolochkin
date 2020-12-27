#pragma once

#include <QDialog>

namespace Ui {
class SizeDialog;
}

class SizeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SizeDialog(QWidget *parent = nullptr);
    ~SizeDialog();
    size_t x;
    size_t y;

private slots:
    void on_spinBoxSizeX_valueChanged(int arg1);
    void on_spinBoxSizeY_valueChanged(int arg1);
    void on_btnOK_clicked();

private:
    Ui::SizeDialog *ui;
    
};
