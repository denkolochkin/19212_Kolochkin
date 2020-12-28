#include "game.h"

GameWidget::GameWidget() : canvasSizeX(10), canvasSizeY(10) {
    canvas.resize(canvasSizeY);
    for(size_t i = 0; i < canvasSizeY; ++i) {
        canvas[i].resize(canvasSizeX, false);
     }
     nextCanvas.resize(canvasSizeY);
     for(size_t i = 0; i < canvasSizeY; ++i) {
         nextCanvas[i].resize(canvasSizeX, false);
     }
     S.push_back(2);
     S.push_back(3);
     B.push_back(3);
}

size_t GameWidget::getCanvasSizeX() { return canvasSizeX; }

size_t GameWidget::getCanvasSizeY() { return canvasSizeY; }

bool GameWidget::checkCell(size_t k, size_t j) { return canvas[k][j]; }

void GameWidget::clear() {
   for(size_t k = 0; k < canvasSizeX; k++) {
      for(size_t j = 0; j < canvasSizeY; j++) {
            canvas[j][k] = false;
      }
   }
}

void GameWidget::mouseEvent(size_t k, size_t j) { canvas[k][j] = !canvas[k][j]; }

void GameWidget::moveEvent(size_t k, size_t j) {
    if(!canvas[k][j]) {
        canvas[k][j] = !canvas[k][j];
    }
}

void GameWidget::resetCanvas() {
    canvas.resize(canvasSizeY);
    for(size_t i = 0; i < canvasSizeY; ++i) {
        canvas[i].resize(canvasSizeX, false);
    }
    nextCanvas.resize(canvasSizeY);
    for(size_t i = 0; i < canvasSizeY; ++i) {
        nextCanvas[i].resize(canvasSizeX, false);
    }
}

bool GameWidget::isAlive(size_t k, size_t j) {
    int neighbors = 0;
    neighbors += canvas[(k + 1) % canvasSizeY]
                       [j % canvasSizeX];
    neighbors += canvas[(k - 1 + canvasSizeY) % canvasSizeY]
                       [j % canvasSizeX];
    neighbors += canvas[k % canvasSizeY]
                       [(j + 1) % canvasSizeX];
    neighbors += canvas[k % canvasSizeY]
                       [(j - 1 + canvasSizeX) % canvasSizeX];
    neighbors += canvas[(k + 1) % canvasSizeY]
                       [(j - 1 + canvasSizeX) % canvasSizeX];
    neighbors += canvas[(k - 1 + canvasSizeY) % canvasSizeY]
                       [(j + 1) % canvasSizeX];
    neighbors += canvas[(k - 1 + canvasSizeY) %canvasSizeY]
                       [(j - 1 + canvasSizeX) % canvasSizeX];
    neighbors += canvas[(k + 1) % canvasSizeY]
                       [(j + 1) % canvasSizeX];
    if(canvas[k][j] && (*std::find(S.begin(), S.end(), neighbors) == neighbors)) {
        return true;
    }
    if(!canvas[k][j] && (*std::find(B.begin(), B.end(), neighbors) == neighbors)) {
        return true;
    }
    return false;
}

bool GameWidget::newGeneration() {
    if(generations < 0) {
        generations++;
    }
    size_t notChanged = 0;
    for(size_t k = 0; k < canvasSizeY; k++) {
        for(size_t j = 0; j < canvasSizeX; j++) {
            nextCanvas[k][j] = isAlive(k, j);
            if(nextCanvas[k][j] == canvas[k][j])
                notChanged++;
        }
    }
    if(notChanged == (canvasSizeX*canvasSizeY)) {
        return false;
    }
    for(size_t k = 0; k < canvasSizeY; k++) {
        for(size_t j = 0; j < canvasSizeX; j++) {
            canvas[k][j] = nextCanvas[k][j];
        }
    }
    generations--;
    if(generations == 0) {
        return false;
    }
    return true;
}

void GameWidget::getB(std::vector<int> b) { B = b; }

void GameWidget::getS(std::vector<int> s) { S = s; }

void GameWidget::setSizeX(size_t x) {
    canvasSizeX = x;
    for (size_t i = 0; i < canvasSizeY; i++) {
        canvas[i].resize(canvasSizeX, false);
    }
    for (size_t i = 0; i < canvasSizeY; i++) {
        nextCanvas[i].resize(canvasSizeX, false);
    }
}

void GameWidget::setSizeY(size_t y) {
    canvasSizeY = y;
    canvas.resize(y);
    for (size_t i = 0; i < canvasSizeY; i++) {
        canvas[i].resize(canvasSizeX, false);
    }
    nextCanvas.resize(y);
    for (size_t i = 0; i < canvasSizeY; i++) {
        nextCanvas[i].resize(canvasSizeX, false);
    }
}

void GameWidget::change(std::string &s, char c, size_t count) {
    if (count == 1) {
        s += c;
    }
    else {
        s += std::to_string(count);
        s += c;
    }
}

void GameWidget::writeCanvas(std::string &s) {
    size_t count = 0;
    bool flag;
    for (size_t i = 0; i < canvasSizeY; ++i) {
        flag = canvas[i][0];
        for (size_t j = 0; j < canvasSizeX; ++j) {
            if (!flag && !canvas[i][j]) {
                count++;
            }
            else if (!flag && canvas[i][j]) {
                change(s, 'b', count);
                count = 1;
                flag = true;
            }
            else if (flag && !canvas[i][j]) {
                change(s, 'o', count);
                count = 1;
                flag = false;
            }
            else {
                count++;
            }
        }
        if (flag) {
            change(s, 'o', count);
        }
        else {
            change(s, 'b', count);
        }
        count = 0;
        s += "$";
    }
    s += "!";
}

void GameWidget::writeRule(std::string &s) {
    s = "B";
    for (auto i : B) {
        s += std::to_string(i);
    }
    s += "/S";
    for (auto i : S) {
        s += std::to_string(i);
    }
}

void GameWidget::writeSizes(std::string &s) {
    s = "x = ";
    s += std::to_string(canvasSizeX);
    s += ", y = ";
    s+= std::to_string(canvasSizeY);
}

bool GameWidget::processFile(const std::string s) {
    size_t x = 0;
    size_t y = 0;
    std::vector<int> newB;
    std::vector<int> newS;
    std::vector<std::vector<bool>> next;
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i] == 'x') {
            i += 4;
            int k = 0;
            while (s[i] != ',') {
                x = x * 10 + (s[i] - '0') ;
                k++;
                i++;
            }
        }
        if (s[i] == 'y') {
            i += 4;
            int k = 0;
            while (s[i] != '\t') {
                y = y * 10 + (s[i]- '0');
                k++;
                i++;
            }
        }
    }
    for (size_t i = 0; i < s.size(); i++) {
        if(s[i] == 'B') {
            i++;
            while(s[i] != '/') {
                if ((s[i] - '0') < 0 || (s[i] - '0') > 9) {
                    return false;
                }
                newB.push_back(s[i] - '0');
                i++;
            }
        }
        if(s[i] == 'S') {
            i++;
            while(s[i] != '\n') {
                if ((s[i] - '0') < 0 || (s[i] - '0') > 9) {
                    return false;
                }
                newS.push_back(s[i] - '0');
                i++;
            }
        }
    }
    next.resize(y);
    for (size_t i = 0; i < y; ++i) {
        next[i].resize(x, false);
    }
    for (size_t i = 0; i < s.size(); i++) {
        if (s[i - 1] == '\n') {
            size_t count = 0;
            size_t position = 0;
            size_t y = 0;
            while(s[i] != '!') {
                if (s[i] == 'o') {
                    next[y][position] = true;
                    i++;
                    position++;
                }
                if (s[i] == 'b') {
                    next[y][position] = false;
                    i++;
                    position++;
                }
                if ((s[i] - '0') >= 0 && (s[i] - '0') <= 9) {
                    count = 0;
                    while(s[i] != 'b' && s[i] != 'o') {
                        count = count * 10 + (s[i] - '0');
                        i++;
                    }
                    if (count < 0 || count > x) {
                        return false;
                    }
                    if (s[i] == 'b') {
                        for(size_t j = 1; j <= count; j++) {
                            next[y][position] = false;
                            position++;
                        }
                        count = 0;
                    }
                    if (s[i] == 'o') {
                        for(size_t j = 1; j <= count; j++) {
                            next[y][position] = true;
                            position++;
                        }
                        count = 0;
                    }
                    i++;
                }
                if(s[i] == '$') {
                    y++;
                    position = 0;
                    i++;
                }
            }
        }
    }
    setSizeX(x);
    setSizeY(y);
    B = newB;
    S = newS;
    canvas = next;
    return true;
 }




