#include "Battleship.h"

Battleship::Battleship(float x, float y, float width, float height) {
    rect.x = x;
    rect.y = y;
    rect.width = width;
    rect.height = height;
    clicked = false;
}

void Battleship::Draw() const {
    if (clicked) {
        DrawRectangleRec(rect, Fade(RED, 1.0f)); // Highlight in red when clicked
    }
}

bool Battleship::IsHovered(Vector2 mousePosition) const {
    return CheckCollisionPointRec(mousePosition, rect);
}

void Battleship::Click() {
    clicked = true;
}

bool Battleship::isClicked() const {
    return clicked;
}
