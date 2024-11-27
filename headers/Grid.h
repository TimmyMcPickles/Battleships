#pragma once
#include "Tile.h"
#include "Battleship.h"
#include <vector>

class Grid {
public:
    Grid(int rows, int cols);
    void Draw() const;
    void Update(Vector2 mousePosition);
    bool IsTileClicked(Vector2 mousePosition);
    bool IsBattleshipClicked(Vector2 mousePosition); // Check if a battleship was clicked

private:
    std::vector<Tile> tiles;
    std::vector<Battleship> battleships; // Vector to store battleships
    int rows;
    int cols;
    void PlaceBattleships();
};
