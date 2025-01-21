#include "MapManager.h"

MapManager::MapManager()
{
	mMap[IMAGE_SIZE][IMAGE_SIZE] = {Tile()};
	mMapImage = Image();
	mMapIndex = 1;
}

MapManager::~MapManager()
{
}

void MapManager::Load()
{
	int index = 0;
	mMapImage = LoadImage(TextFormat("maps/Map%i.png", mMapIndex));
	Color* colors = LoadImageColors(mMapImage);
	int tileSizeX = 1;
	int TileSizeY = 1;
	for (int i = 0; i < mMapImage.width; i++) {
		for (int j = 0; j < mMapImage.width; j++) {
			mMap[i][j] = Tile(j * tileSizeX, i * TileSizeY, tileSizeX, TileSizeY);
			if (colors[index].g > 0 && colors[index].r == 0 && colors[index].b == 0) {
				mMap[i][j].ChangeType(TileType::Normal);
			}
			else if (colors[index].r > 0 && colors[index].g == 0 && colors[index].b == 0) {
				mMap[i][j].ChangeType(TileType::Challenging);
			}
			else if (colors[index].b > 0 && colors[index].r == 0 && colors[index].g == 0) {
				mMap[i][j].ChangeType(TileType::Difficult);
			}
			else if (colors[index].b == 255 && colors[index].r == 255 && colors[index].g == 255) {
				mMap[i][j].ChangeType(TileType::Void);
			}
			else if (colors[index].b == 0 && colors[index].r == 0 && colors[index].g == 0) {
				mMap[i][j].ChangeType(TileType::Obstacle);
			}
			index += 1;
		}
	}
	UnloadImageColors(colors);
	UnloadImage(mMapImage);
}

void MapManager::Start()
{
}

void MapManager::Update()
{
	
}

void MapManager::Draw()
{
	for (int i = 0; i < IMAGE_SIZE; i++) {
		for (int j = 0; j < IMAGE_SIZE; j++) {
			mMap[i][j].Draw();
		}
	}
}

void MapManager::Unload()
{
}

void MapManager::SetMapIndex(int index)
{
	mMapIndex = index;
}

Tile& MapManager::GetTile(int i, int j)
{
	return mMap[j][i];
}

