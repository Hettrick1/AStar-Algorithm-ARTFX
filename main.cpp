#include "raylib.h"
#include "MapManager.h"
#include <iostream>

using namespace std;

MapManager mm;

int main() {

    
    cout << "Hello World" << endl;

    InitWindow(1073, 1073, "My first Raylib window!");
    SetTargetFPS(60);

    mm.Load();

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(GRAY);
        mm.Update();
        mm.Draw();
        EndDrawing();
    }

    CloseWindow();
    return 0;
}