#include "rulesdialog.h"
#include "ui_rulesdialog.h"

RulesDialog::RulesDialog(QWidget *parent) : QDialog(parent), 
                                            countB(9, 0), countS(9, 0), 
                                            ui(new Ui::RulesDialog) {
    ui->setupUi(this);
}

RulesDialog::~RulesDialog() {
    delete ui;
}

void RulesDialog::changeRulesB(size_t index) {
    countB[index]++;
    if (std::find(B.begin(), B.end(), index) == B.end()) {
        B.push_back(index);
    }
    if (countB[index] % 2 == 0) {
      B.erase(std::find(B.begin(), B.end(), index));
    }
}

void RulesDialog::changeRulesS(size_t index) {
    countS[index]++;
    if (std::find(S.begin(), S.end(), index) == S.end()) {
        S.push_back(index);
    }
    if (countS[index] % 2 == 0) {
      S.erase(std::find(S.begin(), S.end(), index));
    }
}

void RulesDialog::on_btnOK_clicked() {
    close();
}

void RulesDialog::on_checkBox_B1_stateChanged() {
    changeRulesB(1);
}

void RulesDialog::on_checkBox_B2_stateChanged() {
    changeRulesB(2);
}

void RulesDialog::on_checkBox_B3_stateChanged() {
    changeRulesB(3);
}

void RulesDialog::on_checkBox_B4_stateChanged() {
    changeRulesB(4);
}

void RulesDialog::on_checkBox_B5_stateChanged() {
    changeRulesB(5);
}

void RulesDialog::on_checkBox_B6_stateChanged() {
    changeRulesB(6);
}

void RulesDialog::on_checkBox_B7_stateChanged() {
    changeRulesB(7);
}

void RulesDialog::on_checkBox_B8_stateChanged() {
    changeRulesB(8);
}

void RulesDialog::on_checkBox_S1_stateChanged() {
    changeRulesS(1);
}

void RulesDialog::on_checkBox_S2_stateChanged() {
    changeRulesS(2);
}

void RulesDialog::on_checkBox_S3_stateChanged() {
    changeRulesS(3);
}

void RulesDialog::on_checkBox_S4_stateChanged() {
    changeRulesS(4);
}

void RulesDialog::on_checkBox_S5_stateChanged() {
    changeRulesS(5);
}

void RulesDialog::on_checkBox_S6_stateChanged() {
    changeRulesS(6);
}

void RulesDialog::on_checkBox_S7_stateChanged() {
    changeRulesS(7);
}

void RulesDialog::on_checkBox_S8_stateChanged() {
    changeRulesS(8);
}
