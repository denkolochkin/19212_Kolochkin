#pragma once

#include <QDialog>

namespace Ui {
class RulesDialog;
}

class RulesDialog : public QDialog {
    Q_OBJECT

public:
    explicit RulesDialog(QWidget *parent = nullptr);
    ~RulesDialog();
    std::vector<int> B;
    std::vector<int> S;
    std::vector<int> countB;
    std::vector<int> countS;


private slots:

    void changeRulesB(size_t index);

    void changeRulesS(size_t index);

    void on_btnOK_clicked();

    void on_checkBox_B1_stateChanged();

    void on_checkBox_B2_stateChanged();

    void on_checkBox_B3_stateChanged();

    void on_checkBox_B4_stateChanged();

    void on_checkBox_B5_stateChanged();

    void on_checkBox_B6_stateChanged();

    void on_checkBox_B7_stateChanged();

    void on_checkBox_B8_stateChanged();

    void on_checkBox_S1_stateChanged();

    void on_checkBox_S2_stateChanged();

    void on_checkBox_S3_stateChanged();

    void on_checkBox_S4_stateChanged();

    void on_checkBox_S5_stateChanged();

    void on_checkBox_S6_stateChanged();

    void on_checkBox_S7_stateChanged();

    void on_checkBox_S8_stateChanged();

private:
    Ui::RulesDialog *ui;
};

