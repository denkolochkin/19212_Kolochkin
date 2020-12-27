#include "rulesdialog.h"
#include "ui_rulesdialog.h"

RulesDialog::RulesDialog(QWidget *parent) : QDialog(parent), countB(9, 0), countS(9, 0), ui(new Ui::RulesDialog) {
    ui->setupUi(this);
}

RulesDialog::~RulesDialog() {
    delete ui;
}

void RulesDialog::on_btnOK_clicked() {
    close();
}

void RulesDialog::on_checkBox_B1_stateChanged() {
    countB[1]++;
    if (std::find(B.begin(), B.end(), 1) == B.end()) {
        B.push_back(1);
    }
    if (countB[1] % 2 == 0) {
      B.erase(std::find(B.begin(), B.end(), 1));
    }
}

void RulesDialog::on_checkBox_B2_stateChanged() {
    countB[2]++;
    if (std::find(B.begin(), B.end(), 2) == B.end()) {
        B.push_back(2);
    }
    if (countB[2] % 2 == 0) {
      B.erase(std::find(B.begin(), B.end(), 2));
    }
}

void RulesDialog::on_checkBox_B3_stateChanged() {
    countB[3]++;
    if (std::find(B.begin(), B.end(), 3) == B.end()) {
        B.push_back(3);
    }
    if (countB[3] % 2 == 0) {
      B.erase(std::find(B.begin(), B.end(), 3));
    }
}

void RulesDialog::on_checkBox_B4_stateChanged() {
    countB[4]++;
    if (std::find(B.begin(), B.end(), 4) == B.end()) {
        B.push_back(4);
    }
    if (countB[4] % 2 == 0) {
      B.erase(std::find(B.begin(), B.end(), 4));
    }
}

void RulesDialog::on_checkBox_B5_stateChanged() {
    countB[5]++;
    if (std::find(B.begin(), B.end(), 5) == B.end()) {
        B.push_back(5);
    }
    if (countB[5] % 2 == 0) {
      B.erase(std::find(B.begin(), B.end(), 5));
    }
}

void RulesDialog::on_checkBox_B6_stateChanged() {
    countB[6]++;
    if (std::find(B.begin(), B.end(), 6) == B.end()) {
        B.push_back(6);
    }
    if (countB[6] % 2 == 0) {
      B.erase(std::find(B.begin(), B.end(), 6));
    }
}

void RulesDialog::on_checkBox_B7_stateChanged() {
    countB[7]++;
    if (std::find(B.begin(), B.end(), 7) == B.end()) {
        B.push_back(7);
    }
    if (countB[7] % 2 == 0) {
      B.erase(std::find(B.begin(), B.end(), 7));
    }
}

void RulesDialog::on_checkBox_B8_stateChanged() {
    countB[8]++;
    if (std::find(B.begin(), B.end(), 8) == B.end()) {
        B.push_back(8);
    }
    if (countB[8] % 2 == 0) {
      B.erase(std::find(B.begin(), B.end(), 8));
    }
}

void RulesDialog::on_checkBox_S1_stateChanged() {
    countS[1]++;
    if (std::find(S.begin(), S.end(), 1) == S.end()) {
        S.push_back(1);
    }
    if (countS[1] % 2 == 0) {
      S.erase(std::find(S.begin(), S.end(), 1));
    }
}

void RulesDialog::on_checkBox_S2_stateChanged() {
    countS[2]++;
    if (std::find(S.begin(), S.end(), 2) == S.end()) {
        S.push_back(2);
    }
    if (countS[2] % 2 == 0) {
      S.erase(std::find(S.begin(), S.end(), 2));
    }
}

void RulesDialog::on_checkBox_S3_stateChanged() {
    countS[3]++;
    if (std::find(S.begin(), S.end(), 3) == S.end()) {
        S.push_back(3);
    }
    if (countS[3] % 2 == 0) {
      S.erase(std::find(S.begin(), S.end(), 3));
    }
}

void RulesDialog::on_checkBox_S4_stateChanged() {
    countS[4]++;
    if (std::find(S.begin(), S.end(), 4) == S.end()) {
        S.push_back(4);
    }
    if (countS[4] % 2 == 0) {
      S.erase(std::find(S.begin(), S.end(), 4));
    }
}

void RulesDialog::on_checkBox_S5_stateChanged() {
    countS[5]++;
    if (std::find(S.begin(), S.end(), 5) == S.end()) {
        S.push_back(5);
    }
    if (countS[5] % 2 == 0) {
      S.erase(std::find(S.begin(), S.end(), 5));
    }
}

void RulesDialog::on_checkBox_S6_stateChanged() {
    countS[6]++;
    if (std::find(S.begin(), S.end(), 6) == S.end()) {
        S.push_back(6);
    }
    if (countS[6] % 2 == 0) {
      S.erase(std::find(S.begin(), S.end(), 6));
    }
}

void RulesDialog::on_checkBox_S7_stateChanged() {
    countS[7]++;
    if (std::find(S.begin(), S.end(), 7) == S.end()) {
        S.push_back(7);
    }
    if (countS[7] % 2 == 0) {
      S.erase(std::find(S.begin(), S.end(), 7));
    }
}

void RulesDialog::on_checkBox_S8_stateChanged() {
    countS[8]++;
    if (std::find(S.begin(), S.end(), 8) == S.end()) {
        S.push_back(8);
    }
    if (countS[8] % 2 == 0) {
      S.erase(std::find(S.begin(), S.end(), 8));
    }
}
