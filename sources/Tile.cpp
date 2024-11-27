#include "Tile.h"

Tile::Tile(float x, float y, float width, float height) {
    rect.x = x;
    rect.y = y;
    rect.width = width;
    rect.height = height;
    state = false;
    clicked = false;
    battleship = nullptr; // Initialize battleship pointer to nullptr
}

void Tile::Draw() const {
    if (battleship && battleship->isClicked()) {
        battleship->Draw();
    } else {
        DrawRectangleRec(rect, Fade(GRAY, clicked ? 0.6f : (state ? 0.6f : 1.0f)));
    }

    // Optional: Draw border for each tile
    DrawRectangleLinesEx(rect, 1, BLACK);
}

bool Tile::IsHovered(Vector2 mousePosition) const {
    return CheckCollisionPointRec(mousePosition, rect);
}

void Tile::SetState(bool newState) {
    state = newState;
}

void Tile::Click() {
    clicked = true;
    if (battleship) {
        battleship->Click(); // Mark the battleship as clicked if it exists
    }
}

bool Tile::isClicked() const {
    return clicked;
}

void Tile::SetBattleship(Battleship* battleship) {
    this->battleship = battleship;
}

bool Tile::HasBattleship() const {
    return battleship != nullptr;
}

// Getter methods
float Tile::GetX() const {
    return rect.x;
}

float Tile::GetY() const {
    return rect.y;
}

float Tile::GetWidth() const {
    return rect.width;
}

float Tile::GetHeight() const {
    return rect.height;
}
