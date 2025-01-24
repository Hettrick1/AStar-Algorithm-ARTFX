#include "raylib.h"
#include "MapManager.h"
#include <iostream>

using namespace std;

MapManager mm;

int main() {

    
    cout << "Hello World" << endl;

    InitWindow(1024, 1024, "My first Raylib window!");
    SetTargetFPS(144);

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