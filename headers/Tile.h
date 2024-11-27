#pragma once
#include "raylib.h"
#include "Battleship.h"

class Tile {
public:
    Tile(float x, float y, float width, float height);
    void Draw() const;
    bool IsHovered(Vector2 mousePosition) const;
    void SetState(bool state);
    void Click();
    bool isClicked() const;
    void SetBattleship(Battleship* battleship);
    bool HasBattleship() const;

    // Getter methods
    float GetX() const;
    float GetY() const;
    float GetWidth() const;
    float GetHeight() const;

private:
    Rectangle rect;
    bool state;
    bool clicked;
    Battleship* battleship; // Pointer to a Battleship object
};
