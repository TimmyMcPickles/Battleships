#pragma once
#include "Grid.h"

class Game {
public:
    Game();
    void Run();

private:
    void Update();
    void Draw();
    int rounds;
    int foundBattleships;
    Grid grid;
    bool gameWon;
    bool gameLost;
};
