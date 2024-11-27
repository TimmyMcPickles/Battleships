#pragma once
#include "raylib.h"

class Battleship {
public:
    Battleship(float x, float y, float width, float height);
    void Draw() const;
    bool IsHovered(Vector2 mousePosition) const;
    void Click();
    bool isClicked() const;

private:
    Rectangle rect;
    bool clicked;
};
