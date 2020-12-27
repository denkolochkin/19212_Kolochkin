#pragma once

#include <vector>
#include <algorithm>
#include <string>

class GameWidget {
public:
    GameWidget();
    size_t getCanvasSizeX();
    size_t getCanvasSizeY();
    bool newGeneration();
    void clear();
    void getB(std::vector<int> b);
    void getS(std::vector<int> s);
    void mouseEvent(size_t k, size_t j);
    void moveEvent(size_t k, size_t j);
    bool checkCell(size_t k, size_t j);
    void setSizeX(size_t x);
    void setSizeY(size_t y);
    void writeRule(std::string &s);
    void writeSizes(std::string &s);
    void writeCanvas(std::string &canvas);
    bool processFile(const std::string s);
private:
    bool isAlive(size_t k, size_t j);
    void resetCanvas();
    void change(std::string &s, char c, size_t count);
    std::vector<std::vector<bool>> canvas;
    std::vector<std::vector<bool>> nextCanvas;
    int generations = -1;
    size_t canvasSizeX;
    size_t canvasSizeY;
    std::vector<int> B;
    std::vector<int> S;
};
