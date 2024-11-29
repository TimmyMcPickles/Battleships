#include "Grid.h"
#include <chrono>
#include <random>
#include <algorithm>
#include <iostream>

Grid::Grid(int rows, int cols) : rows(rows), cols(cols) {
    // Reserve space for all tiles
    tiles.reserve(rows * cols);

    // Create tiles in a grid pattern
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            float x = 150.0f + 130.0f * col;
            float y = 150.0f + 130.0f * row;
            tiles.emplace_back(x, y, 100.0f, 100.0f);
        }
    }

    // Place battleships
    PlaceBattleships();

    // Debug output
    //std::cout << "Total tiles created: " << tiles.size() << std::endl;
}

void Grid::PlaceBattleships() {
    // Reserve space for battleships
    battleships.reserve(5);

    std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::vector<int> positions(tiles.size());
    for (int i = 0; i < positions.size(); ++i) {
        positions[i] = i;
    }

    // Shuffle positions for random placement
    std::shuffle(positions.begin(), positions.end(), generator);

    // Place 5 battleships
    for (int i = 0; i < 5; ++i) {
        int index = positions[i];
        float x = tiles[index].GetX();
        float y = tiles[index].GetY();
        battleships.emplace_back(x, y, tiles[index].GetWidth(), tiles[index].GetHeight());
        tiles[index].SetBattleship(&battleships.back());
    }

    std::cout << "Battleships placed: " << battleships.size() << std::endl;
}

void Grid::Draw() const {
    std::cout << "Drawing grid with " << tiles.size() << " tiles" << std::endl;
    for (const auto& tile : tiles) {
        tile.Draw();
    }
}

void Grid::Update(Vector2 mousePosition) {
    for (auto& tile : tiles) {
        tile.SetState(tile.IsHovered(mousePosition));
    }
}

bool Grid::IsTileClicked(Vector2 mousePosition) {
    for (auto& tile : tiles) {
        if (tile.IsHovered(mousePosition) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            tile.Click();
            return true;
        }
    }
    return false;
}
bool Grid::IsBattleshipClicked(Vector2 mousePosition) {
    for (auto& tile : tiles) {
        if (tile.IsHovered(mousePosition) && tile.HasBattleship() && tile.isClicked()) {
            return true;
        }
    }
    return false;
}
