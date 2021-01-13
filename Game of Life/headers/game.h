#pragma once

#include <vector>

class Game {

public:
    Game();
    size_t getCanvasSizeX(){ return canvasSizeX; };
    size_t getCanvasSizeY(){ return canvasSizeY; };
    void mouseEvent(size_t k, size_t j){ canvas[k][j] = !canvas[k][j]; };
    bool checkCell(size_t k, size_t j){ return canvas[k][j]; };
    void setB(std::vector<int> b){ B = b; };
    void setS(std::vector<int> s){ S = s; };
    bool newGeneration();
    void clear();
    void moveEvent(size_t k, size_t j);
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
