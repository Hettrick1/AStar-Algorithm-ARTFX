#pragma once
#include "raylib.h"
#include "Tile.h"
#include <vector>

#define IMAGE_SIZE 1073

class MapManager
{
private:
	Tile mMap[IMAGE_SIZE][IMAGE_SIZE];
	Image mMapImage;
	int mMapIndex;

public:
	MapManager();
	~MapManager();
	void Load();
	void Start();
	void Update();
	void Draw();
	void Unload();
	void SetMapIndex(int index);
	Tile& GetTile(int i, int j);
};



