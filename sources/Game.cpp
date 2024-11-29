#include "Game.h"
#include "raylib.h"

Game::Game() : rounds(25), foundBattleships(0), grid(5, 5), gameWon(false), gameLost(false) {
    InitWindow(800, 800, "Battleship");
    SetTargetFPS(60);
}

void Game::Run() {
    while (!WindowShouldClose()) {
        Update();
        Draw();
    }
    CloseWindow();
}

void Game::Update() {
    if (!gameWon && !gameLost) {  // Check for both win and loss conditions
        Vector2 mousePosition = GetMousePosition();
        grid.Update(mousePosition);

        if (grid.IsTileClicked(mousePosition)) {
            rounds--;
            if (grid.IsBattleshipClicked(mousePosition)) {
                foundBattleships++;
                if (foundBattleships == 5) {
                    gameWon = true;
                }
            }

            // Check for loss condition
            if (rounds <= 0 && !gameWon) {
                gameLost = true;
            }
        }
    }
}

void Game::Draw() {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    DrawRectangle(0, 100, 800, 25, BLACK);
    DrawRectangle(100, 0, 25, 800, BLACK);

    DrawText(TextFormat("%i", rounds), 20, 20, 70, BLACK);
    for (int i = 0; i < 5; i++) {
        DrawText(TextFormat("%i ", i + 1), 175.0f + 130.0f * (i % 5), 20, 70, BLACK);
        DrawText(TextFormat("%i ", i + 1), 25, 175.0f + 130.0f * (i % 5), 70, BLACK);
    }

    grid.Draw();

    if (gameWon) {
        DrawText("You Win!", 301, 401, 70, BLACK);
        DrawText("You Win!", 299, 399, 70, BLACK);
        DrawText("You Win!", 300, 400, 70, GREEN);
    }else if (gameLost){
        DrawText("Game Over!", 301, 401, 70, BLACK);
        DrawText("Game Over!", 299, 399, 70, BLACK);
        DrawText("Game Over!", 300, 400, 70, MAROON);
    }

    EndDrawing();
}
